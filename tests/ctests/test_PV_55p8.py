import unittest
from random import randint
from PowerViolenceObjects import *

class TestPv_55p8(unittest.TestCase):
    def test_init_with_float(self):
        a: PV_55p8 = PV_55p8()
        self.assertEqual(a._value, 0)

        a: PV_55p8 = PV_55p8(10.0)
        self.assertEqual(a._value, 2560)

        a: PV_55p8 = PV_55p8(-10.0)
        self.assertEqual(a._value, -2560)

        a: PV_55p8 = PV_55p8(0.0)
        self.assertEqual(a._value, 0)

        a: PV_55p8 = PV_55p8(10.55)
        self.assertEqual(a._value, 2700)

    def test_init_with_PV_num(self):
        from PowerViolenceObjects import PV_num, PV_119p8
        a: PV_55p8 = PV_55p8(10.0)
        self.assertEqual(a._value, 2560)

        a: PV_55p8 = PV_55p8(a)
        self.assertEqual(a._value, 2560)

        a: PV_55p8 = PV_55p8(PV_num())
        self.assertEqual(a._value, 0)

        a: PV_55p8 = PV_55p8(PV_119p8())
        self.assertEqual(a._value, 0)

        with self.assertWarns(PV_OverflowWarning):
            a: PV_55p8 = PV_55p8(PV_119p8(float(2**100)))
        self.assertEqual(a._value, 0)

    def test_typename(self):
        a: PV_55p8 = PV_55p8()
        self.assertEqual(a.typename(), 'PV_55p8')
        self.assertEqual(a.typename_int(), 7)

    def test__value(self):
        a: PV_55p8 = PV_55p8()
        a._value = 10
        self.assertEqual(a._value, 10)

        with self.assertRaises(TypeError):
            del a._value

        with self.assertRaises(TypeError):
            a._value = 10.0

        with self.assertRaises(TypeError):
            a._value = '10'

        with self.assertRaises(OverflowError):
            a._value = 10 ** 100

    def test_strvalue(self):
        a: PV_55p8 = PV_55p8()

        a._value = 10
        self.assertEqual(a.strvalue(), '0.0390625')

        a._value = -324523
        self.assertEqual(a.strvalue(), '-1267.66796875')

        a._value = 42323570892357
        self.assertEqual(a.strvalue(), '165326448798.26953125')

    def test_cmp(self):
        a: PV_55p8 = PV_55p8()
        b: PV_55p8 = PV_55p8()
        
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

        with self.assertRaises(TypeError):
            a < '1'

        with self.assertRaises(TypeError):
            a > PV_num()

        c: PV_119p8 = PV_119p8()
        self.assertFalse(a < c)
        self.assertTrue(a > c)
        self.assertFalse(a == c)
        self.assertTrue(a != c)
        self.assertFalse(a <= c)
        self.assertTrue(a >= c)

    def test_hash(self):
        a = PV_55p8()
        
        for i in range(1000):
            a._value = randint(-2**63, 2**63-1)
            self.assertEqual(hash(a), a._value if a._value != -1 else -2)

    def test_str(self):
        a = PV_55p8()

        for i in range(1000):
            a._value = randint(-2**63, 2**63-1)
            self.assertEqual(a.strvalue(), str(a))

    def test_issubclass(self):
        from PowerViolenceObjects import PV_num
        self.assertTrue(issubclass(PV_55p8, PV_num))


if __name__ == '__main__':
    unittest.main()
