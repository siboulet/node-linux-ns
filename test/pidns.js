var ns = require('../build/Release/linux-ns.node');

var execSync = require('child_process').execSync;
var fs = require('fs');

module.exports = {
  'save current pid namespace': function(test) {
    module.pidns = fs.openSync('/proc/self/ns/pid', 'r');
    test.done();
  },

  'create new pid namespace': function(test) {
    ns.unshare(ns.CLONE_NEWPID);
    // The first child process created in namespace has PID 1
    var pid = parseInt(execSync('echo $$').toString());
    test.equal(pid, 1);
    test.done();
  },

  'switch back to origin pid namespace': function(test) {
    ns.setns(module.pidns);
    var pid = parseInt(execSync('echo $$').toString());
    test.notEqual(pid, 1);
    test.done();
  },
};
