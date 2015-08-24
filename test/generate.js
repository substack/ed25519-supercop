var test = require('tape')
var ed = require('../')

test('generate', function (t) {
  t.plan(1)
  var seed = ed.createSeed()
  t.equal(seed.length, 32);
})
