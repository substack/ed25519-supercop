var bindings = require('node-gyp-build')(__dirname)

exports.sign = function (message, publicKey, secretKey) {
  if (typeof message === 'string') message = Buffer.from(message)
  else if (!Buffer.isBuffer(message)) {
    throw new Error('message must be a buffer or a string')
  }
  if (typeof publicKey === 'string') publicKey = Buffer.from(publicKey, 'hex')
  else if (!Buffer.isBuffer(publicKey)) {
    throw new Error('public key must be a buffer or hex string')
  }
  if (typeof secretKey === 'string') secretKey = Buffer.from(secretKey, 'hex')
  else if (!Buffer.isBuffer(secretKey)) {
    throw new Error('secret key must be a buffer or hex string')
  }
  const sig = Buffer.alloc(64)
  bindings.node_supercop_sign(message, publicKey, secretKey, sig)
  return sig
}

exports.verify = function (signature, message, publicKey) {
  if (typeof signature === 'string') signature = Buffer.from(signature, 'hex')
  else if (!Buffer.isBuffer(signature)) {
    throw new Error('message must be a buffer or a string')
  }
  if (typeof message === 'string') message = Buffer.from(message)
  else if (!Buffer.isBuffer(message)) {
    throw new Error('message must be a buffer or a string')
  }
  if (typeof publicKey === 'string') publicKey = Buffer.from(publicKey, 'hex')
  else if (!Buffer.isBuffer(publicKey)) {
    throw new Error('public key must be a buffer or hex string')
  }
  return bindings.node_supercop_verify(signature, message, publicKey) === 1
}

exports.createSeed = function () {
  const seed = Buffer.alloc(32)
  bindings.node_supercop_create_seed(seed)
  return seed
}

exports.createKeyPair = function (seed) {
  if (typeof seed === 'string') seed = Buffer.from(seed, 'hex')
  else if (!Buffer.isBuffer(seed)) {
    throw new Error('seed must be a buffer or hex string')
  }
  const res = {
    publicKey: Buffer.alloc(32),
    secretKey: Buffer.alloc(64)
  }
  bindings.node_supercop_create_key_pair(seed, res.publicKey, res.secretKey)
  return res
}
