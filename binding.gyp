{
  "targets": [
    {
      "target_name": "supercop",
      "sources": [
        "supercop.cc"
      ],
      "include_dirs": ["<!(node -e \"require('nan')\")"]
    }
  ]
}
