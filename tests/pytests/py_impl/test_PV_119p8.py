import unittest
from random import randint
from PowerViolenceObjects.py_impl import *

class TestPv_119p8(unittest.TestCase):
    def test_classvalue(self):
        self.assertEqual(PV_119p8.max_int, 2 ** 127 - 1)
        self.assertEqual(PV_119p8.min_int, -2 ** 127)
        self.assertEqual(PV_119p8.step_int, 256)
        self.assertEqual(PV_119p8.max_float, 2 ** 119 - 2 ** -8)
        self.assertEqual(PV_119p8.min_float, -float(2 ** 119))
        self.assertEqual(PV_119p8.step_float, 0.00390625)

    def test_init_with_float(self):
        a: PV_119p8 = PV_119p8()
        self.assertEqual(a._value, 0)

        a: PV_119p8 = PV_119p8(10.0)
        self.assertEqual(a._value, 2560)

        a: PV_119p8 = PV_119p8(-10.0)
        self.assertEqual(a._value, -2560)

        a: PV_119p8 = PV_119p8(0.0)
        self.assertEqual(a._value, 0)

        a: PV_119p8 = PV_119p8(10.119)
        self.assertEqual(a._value, 2590)

        a: PV_119p8 = PV_119p8(float(2**100))
        self.assertEqual(a._value, 324518553658426726783156020576256)

        with self.assertRaises(TypeError):
            a: PV_119p8 = PV_119p8(10)

    def test_init_with_PV_num(self):
        a = PV_num()
        ans: PV_119p8 = PV_119p8(a)
        self.assertEqual(ans._value, 0)

        b: PV_119p8 = PV_119p8()
        b._value = randint(PV_119p8.min_int, PV_119p8.max_int)
        ans: PV_119p8 = PV_119p8(b)
        self.assertEqual(ans._value, b._value)

        c: PV_55p8 = PV_55p8(10.0)
        ans: PV_119p8 = PV_119p8(c)
        self.assertEqual(ans._value, 2560)

    def test_typename(self):
        a: PV_119p8 = PV_119p8()
        self.assertEqual(type_str(a), 'PV_119p8')
        self.assertEqual(type_int(a), 8)

    def test__value(self):
        a: PV_119p8 = PV_119p8()
        a._value = 10
        self.assertEqual(a._value, 10)

        with self.assertRaises(AttributeError):
            del a._value

        with self.assertRaises(TypeError):
            a._value = 10.0

        with self.assertRaises(TypeError):
            a._value = '10'

        with self.assertRaises(OverflowError):
            def new_fun():
                raise OverflowError
            overflow.func = new_fun
            a._value = 10 ** 100
        
        overflow.func = None

    def test_cmp(self):
        a: PV_119p8 = PV_119p8()
        b: PV_119p8 = PV_119p8()
        
        a._value, b._value = 10, 20
        self.assertTrue(a < b)
        self.assertFalse(a > b)
        self.assertFalse(a == b)
        self.assertTrue(a != b)
        self.assertTrue(a <= b)
        self.assertFalse(a >= b)

        a._value, b._value = 321124, -312412
        self.assertFalse(a < b)
        self.assertTrue(a > b)
        self.assertFalse(a == b)
        self.assertTrue(a != b)
        self.assertFalse(a <= b)
        self.assertTrue(a >= b)

        a._value, b._value = 4145322543523, 4145322543523
        self.assertFalse(a < b)
        self.assertFalse(a > b)
        self.assertTrue(a == b)
        self.assertFalse(a != b)
        self.assertTrue(a <= b)
        self.assertTrue(a >= b)

        c: PV_55p8 = PV_55p8(10.0)
        self.assertFalse(a < c)
        self.assertTrue(a > c)
        self.assertFalse(a == c)
        self.assertTrue(a != c)
        self.assertFalse(a <= c)
        self.assertTrue(a >= c)

        with self.assertRaises(TypeError):
            a < '1'

    def test_hash(self):
        a = PV_119p8()
        b = PV_119p8()
        c = PV_119p8(10.0)
        d = PV_119p8(10.0)
        self.assertEqual(hash(a), hash(b))
        self.assertNotEqual(hash(a), hash(c))
        self.assertNotEqual(hash(a), hash(d))
        self.assertNotEqual(hash(b), hash(c))
        self.assertNotEqual(hash(b), hash(d))
        self.assertEqual(hash(c), hash(d))

    def test_str(self):
        a = PV_119p8()

        a._value = 10
        self.assertEqual(str(a), '0.0390625')

        a._value = -324523
        self.assertEqual(str(a), '-1267.66796875')

        a._value = 42323570892357
        self.assertEqual(str(a), '165326448798.26953125')

        a._value = -2560
        self.assertEqual(str(a), '-10')

    def test_issubclass(self):
        self.assertTrue(issubclass(PV_119p8, PV_num))

    def test_repr(self):
        a = PV_119p8()

        a._value = 10
        self.assertRegex(repr(a), fr'<PV_119p8 object at .*>: _value = \({0}, {10}\)')

        a._value = -324523
        self.assertRegex(repr(a), fr'<PV_119p8 object at .*>: _value = \({-1}, {18446744073709227093}\)')

        a._value = 42323570892357
        self.assertRegex(repr(a), fr'<PV_119p8 object at .*>: _value = \({0}, {42323570892357}\)')


class TestPv_119p8_as_number(unittest.TestCase):
    def test_add(self):
        overflow.func = 'default'

        a: PV_119p8 = PV_119p8()
        b: PV_119p8 = PV_119p8(1.0)
        c: PV_119p8 = a + b
        self.assertEqual(c._value, 256)

        with self.assertRaises(OverflowError):
            a: PV_119p8 = PV_119p8(1e120)
        with self.assertRaises(OverflowError):
            b: PV_119p8 = PV_119p8(1e120)
        a: PV_119p8 = PV_119p8(PV_119p8.max_float / 1.5)
        b: PV_119p8 = PV_119p8(PV_119p8.max_float / 1.5)
        with self.assertRaises(OverflowError):
            a + b
        overflow.func = None
        c: PV_119p8 = a + b
        self.assertEqual(c._value, 0)

        for _ in range(1000):
            a._value = randint(-2**119, 2**119-1)
            b._value = randint(-2**119, 2**119-1)
            trueans: int = a._value + b._value
            if trueans > PV_119p8.max_int or trueans < PV_119p8.min_int:
                trueans = 0
            c = a + b
            self.assertEqual(c._value, trueans)

        d: PV_num = PV_num()
        with self.assertRaises(TypeError):
            a + d

        e: PV_55p8 = PV_55p8()
        e._value = PV_55p8.max_int
        f: PV_119p8 = PV_119p8()
        f._value = PV_55p8.max_int
        g: PV_119p8 = e + f
        self.assertEqual(g._value, 2 * PV_55p8.max_int)

    def test_bool(self):
        a = PV_119p8()
        self.assertFalse(a)

        a = PV_119p8(10000.0)
        self.assertTrue(a)

        a = PV_119p8(-10000.0)
        self.assertTrue(a)

        for i in range(10000):
            a._value = randint(-2**63, 2**63-1)
            if a._value:
                self.assertTrue(a)
            else:
                self.assertFalse(a)


if __name__ == '__main__':
    unittest.main()
