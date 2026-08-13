import unittest
from random import randint
from PowerViolenceObjects.py_impl import *

class TestPv_55p8(unittest.TestCase):
    def test_classvalue(self):
        self.assertEqual(PV_55p8.max_int, 2 ** 63 - 1)
        self.assertEqual(PV_55p8.min_int, -2 ** 63)
        self.assertEqual(PV_55p8.step_int, 256)
        self.assertEqual(PV_55p8.max_float, 2 ** 55 - 2 ** -8)
        self.assertEqual(PV_55p8.min_float, -float(2 ** 55))
        self.assertEqual(PV_55p8.step_float, 0.00390625)

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

        a: PV_55p8 = PV_55p8(2.0 ** 127)
        self.assertEqual(a._value, 0)

        with self.assertRaises(TypeError):
            a: PV_55p8 = PV_55p8(10)

    def test_init_with_PV_num(self):
        a = PV_num()
        b: PV_55p8 = PV_55p8(a)
        self.assertEqual(b._value, 0)

        b._value = randint(PV_55p8.min_int, PV_55p8.max_int)
        c: PV_55p8 = PV_55p8(b)
        self.assertEqual(c._value, b._value)

        d: PV_119p8 = PV_119p8(10.0)
        c: PV_55p8 = PV_55p8(d)
        self.assertEqual(c._value, 2560)

        d: PV_119p8 = PV_119p8(1e100)
        c: PV_55p8 = PV_55p8(d)
        self.assertEqual(c._value, 0)

    def test_typename(self):
        a: PV_55p8 = PV_55p8()
        self.assertEqual(type_str(a), 'PV_55p8')
        self.assertEqual(type_int(a), 7)

    def test__value(self):
        a: PV_55p8 = PV_55p8()
        a._value = 10
        self.assertEqual(a._value, 10)

        with self.assertRaises(AttributeError):
            del a._value

        with self.assertRaises(TypeError):
            a._value = 10.0

        with self.assertRaises(TypeError):
            a._value = '10'

        set_overflow_function('default')
        with self.assertRaises(OverflowError):
            a._value = 10 ** 100
        set_overflow_function(None)

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

    def test_hash(self):
        a = PV_55p8()
        
        for i in range(1000):
            a._value = randint(-2**63, 2**63-1)
            self.assertEqual(hash(a), a._value if a._value != -1 else -2)

    def test_str(self):
        a = PV_55p8()

        a._value = 10
        self.assertEqual(str(a), '0.0390625')

        a._value = -324523
        self.assertEqual(str(a), '-1267.66796875')

        a._value = 42323570892357
        self.assertEqual(str(a), '165326448798.26953125')

        a._value = 256
        self.assertEqual(str(a), '1')

    def test_repr(self):
        a = PV_55p8()

        a._value = 10
        self.assertRegex(repr(a), f'<PV_55p8 object at .*>: _value = {10}')

        a._value = -324523
        self.assertRegex(repr(a), f'<PV_55p8 object at .*>: _value = {-324523}')

        a._value = 42323570892357
        self.assertRegex(repr(a), f'<PV_55p8 object at .*>: _value = {42323570892357}')

    def test_issubclass(self):
        self.assertTrue(issubclass(PV_55p8, PV_num))

    def test_class_id(self):
        self.assertEqual(get_type(7), PV_55p8)
        self.assertEqual(get_type('PV_55p8'), PV_55p8)


class TestPv_55p8_as_number(unittest.TestCase):
    def test_add(self):
        def overflow_func(): raise OverflowError
        set_overflow_function(overflow_func)

        a: PV_55p8 = PV_55p8()
        b: PV_55p8 = PV_55p8(1.0)
        c: PV_55p8 = a + b
        self.assertEqual(c._value, 256)

        a: PV_55p8 = PV_55p8(35028797018963968.0)
        b: PV_55p8 = PV_55p8(35028797018963968.0)
        with self.assertRaises(OverflowError):
            c: PV_55p8 = a + b
        set_overflow_function(None)
        c: PV_55p8 = a + b
        self.assertEqual(c._value, 0)

        for _ in range(1000):
            a._value = randint(-2**63, 2**63-1)
            b._value = randint(-2**63, 2**63-1)
            trueans: int = a._value + b._value
            if trueans > PV_55p8.max_int or trueans < PV_55p8.min_int:
                trueans = 0
            c = a + b
            self.assertEqual(c._value, trueans)

        d: PV_num = PV_num()
        with self.assertRaises(TypeError):
            a + d

    def test_bool(self):
        a = PV_55p8()
        self.assertFalse(a)

        a = PV_55p8(10000.0)
        self.assertTrue(a)

        a = PV_55p8(-10000.0)
        self.assertTrue(a)

        for i in range(10000):
            a._value = randint(-2**63, 2**63-1)
            if a._value:
                self.assertTrue(a)
            else:
                self.assertFalse(a)


if __name__ == '__main__':
    unittest.main()
