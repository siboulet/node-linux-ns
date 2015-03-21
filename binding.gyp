{
  "targets": [
    {
      "target_name": "linux-ns",
      "sources": [ "ns.cc" ],
      "include_dirs" : [ "<!(node -e \"require('nan')\")" ]
    }
  ]
}
