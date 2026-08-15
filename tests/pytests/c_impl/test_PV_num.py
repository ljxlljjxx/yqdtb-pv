import unittest
from PowerViolenceObjects import *

class TestPv_num(unittest.TestCase):
    def test_init(self):
        PV_num()

    def test_add(self):
        a: PV_num = PV_num()
        with self.assertRaises(TypeError):
            a + 5
        with self.assertRaises(TypeError):
            a + a

    def test_overflow_function(self):
        self.assertIs(overflow.func, overflow.initial)

        with overflow.set(True) as of:
            self.assertIsNone(of)
            self.assertIs(overflow.func, overflow.default)
            with self.assertRaises(OverflowError):
                overflow()
        self.assertIs(overflow.func, overflow.initial)

        with self.assertRaises(RuntimeError):
            with overflow.set(False):
                with overflow.set(False):
                    pass

        with self.assertRaises(TypeError):
            with overflow.set(0):
                pass

        overflow.func = False

        with self.assertRaises(OverflowError):
            with overflow.set(True):
                overflow()
        self.assertIs(overflow.func, overflow.initial)

        with overflow.set(True):
            overflow.func = lambda: 5
            self.assertEqual(overflow(), 5)
        self.assertIs(overflow.func, overflow.initial)
        
        with self.assertRaises(TypeError):
            overflow.func = 2

        overflow.func = lambda: 5
        self.assertEqual(overflow(), 5)

        def fun():
            raise RuntimeError
        
        overflow.func = fun
        self.assertIs(overflow.func, fun)

        with overflow.set(True) as of:
            self.assertIsNone(of)
            self.assertIs(overflow.func, overflow.default)
            with self.assertRaises(OverflowError):
                overflow()

        self.assertIs(overflow.func, fun)

        overflow.func = False
        self.assertIs(overflow.func, overflow.initial)

    def test_cmp(self):
        a: PV_num = PV_num()
        b: PV_num = PV_num()
        self.assertTrue(a == b)
        self.assertTrue(a >= b)
        self.assertTrue(a <= b)
        self.assertFalse(a != b)
        self.assertFalse(a > b)
        self.assertFalse(a < b)

        c: int = int()
        with self.assertRaises(TypeError):
            a >= c

        # c: PV_55p8 = PV_55p8()
        # with self.assertRaises(TypeError):
        #     a >= c

    def test_hash(self):
        a: PV_num = PV_num()
        b: PV_num = PV_num()

        self.assertEqual(hash(a), hash(b))

    def test_repr(self):
        a: PV_num = PV_num()
        b: PV_num = PV_num()

        self.assertNotEqual(repr(a), repr(b))
        self.assertEqual(repr(a), repr(a))

    def test_functions(self):
        a: PV_num = PV_num()
        self.assertEqual(get_type(type_int(a)), PV_num)
        self.assertEqual(get_type(type_str(a)), PV_num)
        self.assertEqual(typestr_int(type_str(a)), 0)
        self.assertEqual(typeint_str(type_int(a)), "PV_num")
        self.assertEqual(type_int(PV_num), 0)
        self.assertEqual(type_str(PV_num), "PV_num")
        self.assertEqual(typetype_type(type_int(PV_num), type_int(PV_num)), type_int(PV_num))
        with self.assertRaises(TypeError): type_int('a')
        with self.assertRaises(TypeError): type_str('a')
        with self.assertRaises(TypeError): typestr_int(1)
        with self.assertRaises(TypeError): typeint_str('a')
        with self.assertRaises(TypeError): get_type(())
        with self.assertRaises(TypeError): typetype_type(PV_num, PV_num)
        with self.assertRaises(ValueError): type_int(int)
        with self.assertRaises(ValueError): type_str(int)
        with self.assertRaises(ValueError): typestr_int('int')
        with self.assertRaises(ValueError): typeint_str(2541)
        with self.assertRaises(ValueError): get_type(2541)
        with self.assertRaises(ValueError): get_type('2541')
        with self.assertRaises(ValueError): typetype_type(1, 2541)
        with self.assertRaises(RuntimeError): get_type(2)

    def test_class_id(self):
        self.assertEqual(get_type(0), PV_num)
        self.assertEqual(get_type('PV_num'), PV_num)



if __name__ == '__main__':
    unittest.main()
