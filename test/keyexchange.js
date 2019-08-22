var test = require('tape')
var ed = require('../')

test('exchanging keys', function (t) {
  t.plan(1);

  var kp1 = ed.createKeyPair(ed.createSeed());
  var kp2 = ed.createKeyPair(ed.createSeed());

  var s1 = ed.exchangeKeys(kp1.publicKey, kp2.secretKey);
  var s2 = ed.exchangeKeys(kp2.publicKey, kp1.secretKey);

  t.equal(s1.toString('hex'), s2.toString('hex'));
})
