import unittest
from PowerViolenceObjects.py_impl import PV_binary

class TestPv_str(unittest.TestCase):
    def test_init(self):
        with self.assertRaises(TypeError):
            PV_binary()
        with self.assertRaises(TypeError):
            PV_binary(0.1)
        with self.assertRaises(ValueError):
            PV_binary(-1)
        with self.assertRaises(OverflowError):
            PV_binary(65536)
        a = PV_binary(5)
        self.assertEqual(a.size, 5)
        self.assertEqual(len(list(a.data)), 5)
        a = PV_binary(5, 0)
        self.assertEqual(a.size, 5)
        self.assertEqual(len(list(a.data)), 5)
        a = PV_binary(5, False)
        with self.assertRaises(ValueError):
            a = PV_binary(5, 2)
        with self.assertRaises(TypeError):
            a = PV_binary(5, '2')
        self.assertEqual(a.size, 5)
        self.assertEqual(len(list(a.data)), 5)
        b = PV_binary(a)
        self.assertEqual(b.size, 5)
        self.assertEqual(len(list(b.data)), 5)
        c = PV_binary(False for _ in range(4))
        self.assertEqual(c.size, 4)
        self.assertEqual(list(c.data), [False for _ in range(4)])
        c = PV_binary(1 for _ in range(4))
        self.assertEqual(c.size, 4)
        self.assertEqual(list(c.data), [True for _ in range(4)])
        with self.assertRaises(ValueError):
            c = PV_binary(2 for _ in range(4))
        with self.assertRaises(TypeError):
            c = PV_binary('1' for _ in range(4))

    def test_size(self):
        a = PV_binary(5)
        with self.assertRaises(AttributeError):
            a.size = 4
        self.assertEqual(a.size, 5)
        with self.assertRaises(AttributeError):
            del a.size

    def test_data(self):
        a = PV_binary((0, 0, 0, 0, 0))
        with self.assertRaises(AttributeError):
            a.data = b'2541'
        for i in a.data:
            self.assertIs(i, False)
        with self.assertRaises(AttributeError):
            del a.data

    def test_repr(self):
        a = PV_binary((0, 1, 0, 1, 0))
        self.assertEqual(repr(a), f'<PV_binary object at {id(a)}, size = 5>: [0, 1, 0, 1, 0]')

    def test_str(self):
        a = PV_binary((0, 1, 0, 1, 0))
        self.assertEqual(str(a), f'<PV_binary object size = 5>: [0, 1, 0, 1, 0]')

    def test_eq(self):
        a = PV_binary((0, 1, 0, 1, 0))
        b = PV_binary((0, 1, 0, 1, 0))
        self.assertEqual(a, b)
        c = PV_binary((0, 1, 0, 1, 1))
        self.assertNotEqual(a, c)
        self.assertNotEqual(b, c)

    def test_hash(self):
        a = PV_binary((0, 1, 0, 1, 0))
        self.assertEqual(hash(a), 10)
    
    def test_bool(self):
        a = PV_binary((0, 1, 0, 1, 0))
        with self.assertRaises(TypeError):
            if a:
                pass
        with self.assertRaises(TypeError):
            bool(a)

    def test_len(self):
        a = PV_binary((0, 1, 0, 1, 0))
        self.assertEqual(len(a), 5)

    def test_item(self):
        a = PV_binary((0, 1, 0, 1, 0))
        self.assertEqual(a[0], False)
        self.assertEqual(a[1], True)
        self.assertEqual(a[2], False)
        self.assertEqual(a[3], True)
        self.assertEqual(a[4], False)
        self.assertEqual(a[-5], False)
        self.assertEqual(a[-4], True)
        self.assertEqual(a[-3], False)
        self.assertEqual(a[-2], True)
        self.assertEqual(a[-1], False)
        with self.assertRaises(ValueError):
            a[6]
        with self.assertRaises(TypeError):
            a['6']
        with self.assertRaises(ValueError):
            a[0] = 5
        with self.assertRaises(TypeError):
            a[0] = '5'
        a[0] = True
        self.assertEqual(a[0], True)
        a[-5] = 0
        self.assertEqual(a[0], False)
        with self.assertRaises(ValueError):
            a[6] = 1
        with self.assertRaises(TypeError):
            a['6'] = 1
        a[:] = 0
        for i in range(5):
            self.assertEqual(a[i], False)
        a[::] = 1
        for i in range(5):
            self.assertEqual(a[i], True)
        with self.assertRaises(ValueError):
            a[1:1] = 1
        with self.assertRaises(ValueError):
            a[::-1] = 1
        with self.assertRaises(TypeError):
            del a[-1]

    def test_int(self):
        a = PV_binary(10, 0)
        self.assertEqual(int(a), 0)
        a[4] = a[5] = 1
        self.assertEqual(int(a), 48)


if __name__ == '__main__':
    unittest.main()
