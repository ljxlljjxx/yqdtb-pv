import unittest
from PowerViolenceObjects import *
import PowerViolenceObjects as PVOs

class TestPv_num(unittest.TestCase):
    def test_init(self):
        PV_num()

    def test_number(self):
        a: PV_num = PV_num()
        with self.assertRaises(TypeError): a + 1
        with self.assertRaises(TypeError): a >> 1
        with self.assertRaises(TypeError): a & 1
        with self.assertRaises(TypeError): int(a)
        with self.assertRaises(TypeError): pow(a, 100)
        with self.assertRaises(TypeError): a *= 2

    def test_overflow_function(self):
        self.assertIsNone(get_overflow_function())
        
        with self.assertRaises(TypeError):
            set_overflow_function(2)

        set_overflow_function(lambda: 5)
        self.assertEqual(get_overflow_function(), 5)

    def test_typename(self):
        a: PV_num = PV_num()
        self.assertEqual(a.typename(), 'PV_num')
        self.assertEqual(a.typename_int(), 0)

    def test_cmp(self):
        a: PV_num = PV_num()
        b: PV_num = PV_num()
        self.assertTrue(a == b)
        self.assertTrue(a >= b)
        self.assertTrue(a <= b)
        self.assertFalse(a != b)
        self.assertFalse(a > b)
        self.assertFalse(a < b)

        c: PV_55p8 = PV_55p8()
        with self.assertRaises(TypeError):
            a >= c

    def test_hash(self):
        a: PV_num = PV_num()
        b: PV_num = PV_num()

        self.assertEqual(hash(a), hash(b))

    def test_functions(self):
        from PowerViolenceObjects import get_type, type_int, type_str, typestr_int, typeint_str, typetype_type
        a: PV_num = PV_num()
        self.assertEqual(get_type(a.typename_int()), PV_num)
        self.assertEqual(get_type(a.typename()), PV_num)
        self.assertEqual(typestr_int(a.typename()), 0)
        self.assertEqual(typeint_str(a.typename_int()), "PV_num")
        self.assertEqual(type_int(PV_num), 0)
        self.assertEqual(type_str(PV_num), "PV_num")
        self.assertEqual(typetype_type(type_int(PV_num), type_int(PV_num)), type_int(PV_num))


if __name__ == '__main__':
    unittest.main()
