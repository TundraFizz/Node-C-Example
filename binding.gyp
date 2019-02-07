{
  "targets": [{
    "target_name": "screen-capture",
    "include_dirs" : [
      "src",
      "<!(node -e \"require('nan')\")"
    ],
    "sources": [
      "src/cpp/sample.cpp"
    ],
    "msvs_settings": {
      "VCCLCompilerTool": {
        "WarnAsError": "true"
      }
    }
  }]
}
