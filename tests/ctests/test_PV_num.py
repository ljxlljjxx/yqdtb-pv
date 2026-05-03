import unittest
from PowerViolenceObjects import PV_num

class TestPv_num(unittest.TestCase):
    def test_PowerViolenceObjects(self):
        import PowerViolenceObjects as PVOs
        self.assertEqual(PVOs.__version__, '2.2.4')

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


if __name__ == '__main__':
    unittest.main()
