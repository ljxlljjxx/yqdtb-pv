import unittest
from PowerViolenceObjects import PV_binary

class TestPv_str(unittest.TestCase):
    def test_init(self):
        with self.assertRaises(TypeError):
            PV_binary()
        with self.assertRaises(TypeError):
            PV_binary(0.1)
        with self.assertRaises(ValueError):
            PV_binary(-1)
        a = PV_binary(5)
        self.assertEqual(a.size, 5)
        self.assertEqual(a.data, bytearray(5))
        b = PV_binary(a)
        self.assertEqual(b.size, 5)
        self.assertEqual(b.data, bytearray(5))
        self.assertIsNot(a.data, b.data)
        c = PV_binary(b'2541')
        self.assertEqual(c.size, 4)
        self.assertEqual(c.data, bytearray(b'2541'))

    def test_repr(self):
        a = PV_binary(5)
        self.assertEqual(repr(a), '<PV_binary object, size = 5>: [0, 0, 0, 0, 0]')

    def test_data(self):
        a = PV_binary(5)
        with self.assertRaises(ValueError):
            a.data = b'2541'
        a.data = b'2541a'
        self.assertEqual(a.data, b'2541a')
        with self.assertRaises(AttributeError):
            del a.data


if __name__ == '__main__':
    unittest.main()
