#include <nan.h>
#include <ldap.h>

struct SASLDefaults {
  SASLDefaults(
    const v8::Local<v8::Value>& usr,
    const v8::Local<v8::Value>& pw,
    const v8::Local<v8::Value>& rlm,
    const v8::Local<v8::Value>& proxy
  ) : 
    user(Get(usr)), 
    password(Get(pw)),
    realm(Get(rlm)), 
    proxy_user(Get(proxy))
  {}

  // Returns a C NULL value if not a string 
  static inline v8::Local<v8::Value> Get(const v8::Local<v8::Value>& v) {
    return v->IsString() ? v : v8::Local<v8::Value>();
  }

  static int Callback(LDAP *ld, unsigned flags, void *defaults, void *in);

  v8::String::Utf8Value user;
  v8::String::Utf8Value password;
  v8::String::Utf8Value realm;
  v8::String::Utf8Value proxy_user;

private:
  void Set(unsigned flags, sasl_interact_t *interact);
};

