{
  "targets": [
    {
      "target_name": "supercop",
      "sources": [
        "supercop.cc",
        "vendor/ed25519/add_scalar.c",
        "vendor/ed25519/fe.c",
        "vendor/ed25519/ge.c",
        "vendor/ed25519/key_exchange.c",
        "vendor/ed25519/keypair.c",
        "vendor/ed25519/sc.c",
        "vendor/ed25519/seed.c",
        "vendor/ed25519/sha512.c",
        "vendor/ed25519/sign.c",
        "vendor/ed25519/verify.c"
      ],
      "include_dirs": ["<!(node -e \"require('nan')\")"]
    }
  ]
}
