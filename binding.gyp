{
  "targets": [
    {
      "target_name": "supercop",
      "sources": [
        "supercop.cc",
        "vendor/ed25519/src/sign.c"
      ],
      "include_dirs": ["<!(node -e \"require('nan')\")"]
    }
  ]
}
