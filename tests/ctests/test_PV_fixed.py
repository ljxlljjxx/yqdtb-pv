import unittest
from PowerViolenceObjects import PV_fixed

class TestPv_fixed(unittest.TestCase):
    def test_init(self):
        PV_fixed()

    def test_fixedber(self):
        a: PV_fixed = PV_fixed()
        with self.assertRaises(TypeError): a + 1
        with self.assertRaises(TypeError): a >> 1
        with self.assertRaises(TypeError): a & 1
        with self.assertRaises(TypeError): int(a)
        with self.assertRaises(TypeError): pow(a, 100)
        with self.assertRaises(TypeError): a *= 2


if __name__ == '__main__':
    unittest.main()
