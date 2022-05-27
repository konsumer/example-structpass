/* global describe, test, expect */

import ref from 'ref-napi'
import refStruct from 'ref-struct-di'
import bindings from 'bindings'

const StructType = refStruct(ref)

const addon = bindings('hello')

// GENERATED
const Vector2 = StructType({
  x: ref.types.float,
  y: ref.types.float
})

// GENERATED
function hello (v) {
  addon.hello(parseInt(v.ref().hexAddress(), 16))
}

describe('Vector2', () => {
  test('should be able to make a Vector2 and set stuff like normal', () => {
    const v = new Vector2({ x: 10, y: 20 })
    expect(v.x).toBe(10)
    expect(v.y).toBe(20)
  })

  test('should be able to call into C with it', () => {
    const v = new Vector2({ x: 10, y: 20 })
    console.log(hello(v))
  })
})
