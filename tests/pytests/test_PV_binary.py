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
        a = PV_binary(b'2541a')
        self.assertEqual(repr(a), f'<PV_binary object at {id(a)}, size = 5>: [50, 53, 52, 49, 97]')

    def test_str(self):
        a = PV_binary(b'2541a')
        self.assertEqual(str(a), f'<PV_binary object size = 5>: [50, 53, 52, 49, 97]')

    def test_bytes(self):
        a = PV_binary(b'2541a')
        self.assertEqual(bytes(a), b'2541a')

    def test_eq(self):
        a = PV_binary(b'2541a')
        b = PV_binary(b'2541a')
        self.assertEqual(a, b)
        c = PV_binary(b'2541b')
        self.assertNotEqual(a, c)
        self.assertNotEqual(b, c)

    def test_hash(self):
        a = PV_binary(b'2541a')
        self.assertEqual(hash(a), hash(b'2541a'))
    
    def test_bool(self):
        a = PV_binary(b'2541a')
        with self.assertRaises(TypeError):
            if a:
                pass
        with self.assertRaises(TypeError):
            bool(a)

    def test_len(self):
        a = PV_binary(b'2541a')
        self.assertEqual(len(a), 5)

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
