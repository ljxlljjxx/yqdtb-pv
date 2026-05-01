import unittest
from PowerViolenceObjects.PV_55p8 import PV_55p8

class TestPv_55p8(unittest.TestCase):
    def test_init(self):
        a: PV_55p8 = PV_55p8()
        self.assertEqual(a.strvalue(), '0')

        a: PV_55p8 = PV_55p8(10)
        self.assertEqual(a.strvalue(), '10.0')

        a: PV_55p8 = PV_55p8(-10)
        self.assertEqual(a.strvalue(), '-10.0')

        a: PV_55p8 = PV_55p8(0)
        self.assertEqual(a.strvalue(), '0')

        a: PV_55p8 = PV_55p8(10.55)
        self.assertEqual(a.strvalue(), '10.546875')

    def test__value(self):
        a: PV_55p8 = PV_55p8()
        a._value = 10
        self.assertEqual(a.strvalue(), '0.0390625')
        self.assertEqual(a._value, 10)
        with self.assertRaises(TypeError):
            del a._value

        with self.assertRaises(TypeError):
            a._value = 10.0

        with self.assertRaises(TypeError):
            a._value = '10'

        with self.assertRaises(OverflowError):
            a._value = 10 ** 100

if __name__ == '__main__':
    unittest.main()
