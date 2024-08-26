
#include <string.h>
#include <node.h>
#include <node_buffer.h>
#include <v8.h>
#include "sign.h"


void GenerateKeypair(const v8::FunctionCallbackInfo<v8::Value>& args) {
    v8::Isolate* isolate = args.GetIsolate();

    unsigned char pk[256];
    unsigned char sk[512];

    // تولید کلیدها
    crypto_sign_keypair(pk, sk);

    // ایجاد و مقداردهی ArrayBuffer برای کلید عمومی
    v8::Local<v8::ArrayBuffer> publicKeyBuffer = v8::ArrayBuffer::New(isolate, 512);
    unsigned char* pk_copy;
    #if NODE_MAJOR_VERSION >= 14
        pk_copy = static_cast<unsigned char*>(publicKeyBuffer->GetBackingStore()->Data());
    #else
        pk_copy = static_cast<unsigned char*>(publicKeyBuffer->GetContents().Data());
    #endif
    memcpy(pk_copy, pk, 256);

    // ایجاد و مقداردهی ArrayBuffer برای کلید خصوصی
    v8::Local<v8::ArrayBuffer> privateKeyBuffer = v8::ArrayBuffer::New(isolate, 512);
    unsigned char* sk_copy;
    #if NODE_MAJOR_VERSION >= 14
        sk_copy = static_cast<unsigned char*>(privateKeyBuffer->GetBackingStore()->Data());
    #else
        sk_copy = static_cast<unsigned char*>(privateKeyBuffer->GetContents().Data());
    #endif
    memcpy(sk_copy, sk, 512);

    // ایجاد یک شیء جاوااسکریپت برای بازگشت کلیدها
    v8::Local<v8::Object> keypair = v8::Object::New(isolate);

    v8::MaybeLocal<v8::String> publicKeyStr = v8::String::NewFromUtf8(isolate, "publicKey", v8::NewStringType::kNormal);
    v8::MaybeLocal<v8::String> privateKeyStr = v8::String::NewFromUtf8(isolate, "privateKey", v8::NewStringType::kNormal);

    if (!publicKeyStr.IsEmpty() && !privateKeyStr.IsEmpty()) {
        keypair->Set(isolate->GetCurrentContext(),
                     publicKeyStr.ToLocalChecked(),
                     node::Buffer::Copy(isolate, reinterpret_cast<char*>(pk_copy), 512).ToLocalChecked()).FromJust();

        keypair->Set(isolate->GetCurrentContext(),
                     privateKeyStr.ToLocalChecked(),
                     node::Buffer::Copy(isolate, reinterpret_cast<char*>(sk_copy), 512).ToLocalChecked()).FromJust();
    }

    args.GetReturnValue().Set(keypair);
}

void SignMessage(const v8::FunctionCallbackInfo<v8::Value>& args) {
    v8::Isolate* isolate = args.GetIsolate();

    v8::Local<v8::Uint8Array> message = args[0].As<v8::Uint8Array>();
    v8::Local<v8::Uint8Array> secretKey = args[1].As<v8::Uint8Array>();

    unsigned long sm_size = 10000;
    unsigned char* sm = (unsigned char*)malloc(sm_size);
    unsigned long long smlen;

    // امضا کردن پیام
    unsigned char* message_data;
    unsigned char* secretKey_data;
    #if NODE_MAJOR_VERSION >= 14
        message_data = static_cast<unsigned char*>(message->Buffer()->GetBackingStore()->Data());
        secretKey_data = static_cast<unsigned char*>(secretKey->Buffer()->GetBackingStore()->Data());
    #else
        // استفاده از CopyContents برای نسخه‌های قدیمی‌تر
        message_data = static_cast<unsigned char*>(malloc(message->Length()));
        secretKey_data = static_cast<unsigned char*>(malloc(secretKey->Length()));
        message->CopyContents(message_data, message->Length());
        secretKey->CopyContents(secretKey_data, secretKey->Length());
    #endif

    crypto_sign(sm, &smlen, message_data, message->Length(), secretKey_data);

    // ایجاد یک ArrayBuffer برای امضای پیام
    v8::Local<v8::ArrayBuffer> buffer = v8::ArrayBuffer::New(isolate, smlen);
    unsigned char* buffer_data;
    #if NODE_MAJOR_VERSION >= 14
        buffer_data = static_cast<unsigned char*>(buffer->GetBackingStore()->Data());
    #else
        buffer_data = static_cast<unsigned char*>(buffer->GetContents().Data());
    #endif
    memcpy(buffer_data, sm, smlen);

    free(sm);

    args.GetReturnValue().Set(v8::Uint8Array::New(buffer, 0, smlen));
}

void VerifySignature(const v8::FunctionCallbackInfo<v8::Value>& args) {
    v8::Isolate* isolate = args.GetIsolate();

    v8::Local<v8::Uint8Array> sm = args[0].As<v8::Uint8Array>();
    v8::Local<v8::Uint8Array> message = args[1].As<v8::Uint8Array>();
    v8::Local<v8::Uint8Array> publicKey = args[2].As<v8::Uint8Array>();

    unsigned char* sm_data;
    unsigned char* message_data;
    unsigned char* publicKey_data;
    #if NODE_MAJOR_VERSION >= 14
        sm_data = static_cast<unsigned char*>(sm->Buffer()->GetBackingStore()->Data());
        message_data = static_cast<unsigned char*>(message->Buffer()->GetBackingStore()->Data());
        publicKey_data = static_cast<unsigned char*>(publicKey->Buffer()->GetBackingStore()->Data());
    #else
        // استفاده از CopyContents برای نسخه‌های قدیمی‌تر
        sm_data = static_cast<unsigned char*>(malloc(sm->Length()));
        message_data = static_cast<unsigned char*>(malloc(message->Length()));
        publicKey_data = static_cast<unsigned char*>(malloc(publicKey->Length()));
        sm->CopyContents(sm_data, sm->Length());
        message->CopyContents(message_data, message->Length());
        publicKey->CopyContents(publicKey_data, publicKey->Length());
    #endif

    // بررسی امضا
    int result = crypto_sign_verify(sm_data, sm->Length(), message_data, message->Length(), publicKey_data);

    args.GetReturnValue().Set(v8::Boolean::New(isolate, result == 0));

    #if NODE_MAJOR_VERSION < 14
        free(sm_data);
        free(message_data);
        free(publicKey_data);
    #endif
}

void Initialize(v8::Local<v8::Object> exports) {
    NODE_SET_METHOD(exports, "generateKeypair", GenerateKeypair);
    NODE_SET_METHOD(exports, "signMessage", SignMessage);
    NODE_SET_METHOD(exports, "verifySignature", VerifySignature);
}

NODE_MODULE(NODE_GYP_MODULE_NAME, Initialize)
