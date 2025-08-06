import array
import random
import fastsci.core as fct
import numpy as np

class Array:
    def __init__(self, data, shape=None, dtype='float64'):
        if dtype == 'float64':
            self.typecode = 'd'
        else:
            raise NotImplementedError(f"dtype '{dtype}' not supported yet")

        if isinstance(data, list):
            self.buffer = array.array(self.typecode, data)
        elif isinstance(data, array.array) and data.typecode == self.typecode:
            self.buffer = data
        else:
            raise TypeError("Array requires a list or array.array of float64")

        self.shape = shape or (len(self.buffer),)
        self.size = len(self.buffer)
        self.dtype = dtype

    def mean(self):
        return fct.stats.mean(self.buffer)

    def stddev(self):
        return fct.stats.stddev(self.buffer)

    def __add__(self, other):
        if isinstance(other, Array):
            result_bytes = fct.stats.add_arrays(self.buffer, other.buffer)
            result_array = array.array(self.typecode)
            result_array.frombytes(result_bytes)
            return Array(result_array, shape=self.shape)
        elif isinstance(other, (int, float)):
            result_bytes = fct.matrix.add_scalar(self.buffer, float(other))
            result_array = array.array(self.typecode)
            result_array.frombytes(result_bytes)
            return Array(result_array, shape=self.shape)
        else:
            raise TypeError("Unsupported operand for +")

    def __mul__(self, other):
        if isinstance(other, Array):
            # future: implement mul_arrays in C for performance
            return Array([a * b for a, b in zip(self.buffer, other.buffer)], shape=self.shape)
        elif isinstance(other, (int, float)):
            result_bytes = fct.matrix.mul_scalar(self.buffer, float(other))
            result_array = array.array(self.typecode)
            result_array.frombytes(result_bytes)
            return Array(result_array, shape=self.shape)
        else:
            raise TypeError("Unsupported operand for *")


    @classmethod
    def zeros(cls, shape):
        size = cls._shape_size(shape)
        return cls([0.0] * size, shape=shape)

    @classmethod
    def ones(cls, shape):
        size = cls._shape_size(shape)
        return cls([1.0] * size, shape=shape)

    @classmethod
    def random(cls, shape, low=0.0, high=1.0):
        size = cls._shape_size(shape)
        data = [random.uniform(low, high) for _ in range(size)]
        return cls(data, shape=shape)

    @staticmethod
    def _shape_size(shape):
        size = 1
        for dim in shape:
            size *= dim
        return size
    
    def to_numpy(self):
        try:
            import numpy as np
        except ImportError:
            raise ImportError("NumPy is not installed. Run: pip install fastsci[numpy]")
        return np.array(self.buffer, dtype=self.dtype).reshape(self.shape)

    @classmethod
    def from_numpy(cls, np_array):
        try:
            import numpy as np
        except ImportError:
            raise ImportError("NumPy is not installed. Run: pip install fastsci[numpy]")
        flat = np_array.flatten().tolist()
        shape = np_array.shape
        return cls(flat, shape=shape, dtype=str(np_array.dtype))

    def __repr__(self):
        return f"Array(shape={self.shape}, dtype={self.dtype}, data={list(self.buffer)})"
