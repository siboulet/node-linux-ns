#include <nan.h>
#include <sched.h>

using namespace v8;

NAN_METHOD(Setns) {
  NanScope();

  int fd = args[0]->IntegerValue();
  int nstype = (args[1]->IsNumber()) ? args[1]->IntegerValue() : 0;

  if (setns(fd, nstype) != 0) {
    return NanThrowError(strerror(errno), errno);
  }

  NanReturnNull();
}

NAN_METHOD(Unshare) {
  NanScope();

  int flags = args[0]->IntegerValue();

  if (unshare(flags) != 0) {
    return NanThrowError(strerror(errno), errno);
  }

  NanReturnNull();
}

void Init(Handle<Object> exports) {
  exports->Set(NanNew("setns"), NanNew<FunctionTemplate>(Setns)->GetFunction());
  exports->Set(NanNew("unshare"), NanNew<FunctionTemplate>(Unshare)->GetFunction());

  // Flags from /usr/include/linux/sched.h
  exports->Set(NanNew("CLONE_NEWNS"), NanNew<Number>(CLONE_NEWNS)); /* New namespace group? */
  exports->Set(NanNew("CLONE_NEWUTS"), NanNew<Number>(CLONE_NEWUTS)); /* New utsname group? */
  exports->Set(NanNew("CLONE_NEWIPC"), NanNew<Number>(CLONE_NEWIPC)); /* New ipcs */
  exports->Set(NanNew("CLONE_NEWUSER"), NanNew<Number>(CLONE_NEWUSER)); /* New user namespace */
  exports->Set(NanNew("CLONE_NEWPID"), NanNew<Number>(CLONE_NEWPID)); /* New pid namespace */
  exports->Set(NanNew("CLONE_NEWNET"), NanNew<Number>(CLONE_NEWNET)); /* New network namespace */
}

NODE_MODULE(ns, Init)
