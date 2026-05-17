import unittest
from PowerViolenceObjects import PV_num

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

    def test_typename(self):
        a: PV_num = PV_num()
        self.assertEqual(a.typename(), 'PV_num')
        self.assertEqual(a.typename_int(), 0)

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
