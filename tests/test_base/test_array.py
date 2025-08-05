import unittest
from fastsci.base import Array

class TestArray(unittest.TestCase):
    def test_basic_init(self):
        a = Array([1.0, 2.0, 3.0])
        self.assertEqual(a.shape, (3,))
        self.assertEqual(a.size, 3)
        self.assertEqual(a.dtype, 'float64')

    def test_zeros_ones(self):
        z = Array.zeros((4,))
        o = Array.ones((4,))
        self.assertTrue(all(v == 0.0 for v in z.buffer))
        self.assertTrue(all(v == 1.0 for v in o.buffer))

    def test_random_range(self):
        r = Array.random((5,), low=5, high=10)
        self.assertTrue(all(5 <= v <= 10 for v in r.buffer))

    def test_add_scalar(self):
        a = Array([1.0, 2.0])
        b = a + 3
        self.assertEqual(list(b.buffer), [4.0, 5.0])

    def test_add_array(self):
        a = Array([1.0, 2.0])
        b = Array([3.0, 4.0])
        c = a + b
        self.assertEqual(list(c.buffer), [4.0, 6.0])

    def test_mul_scalar(self):
        a = Array([2.0, 3.0])
        b = a * 2
        self.assertEqual(list(b.buffer), [4.0, 6.0])

    def test_numpy_optional(self):
        try:
            import numpy as np
            a = Array([1.0, 2.0])
            np_arr = a.to_numpy()
            self.assertTrue(isinstance(np_arr, np.ndarray))

            b = Array.from_numpy(np.array([5.0, 6.0]))
            self.assertEqual(list(b.buffer), [5.0, 6.0])
        except ImportError:
            self.skipTest("NumPy not installed")

if __name__ == '__main__':
    unittest.main()
