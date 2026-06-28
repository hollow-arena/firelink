from functools import wraps
from collections.abc import Callable
from typing import Optional

_registry: list[dict] = []

def udf(description: Optional[str] = None, params: Optional[dict[str, str]] = None):
    def udf_docstrings(func: Callable):
        _registry.append({
            "name": func.__name__,
            "description": description or "",
            "params": params or {},
        })
        @wraps(func)
        def wrapper(*args, **kwargs):
            return func(*args, **kwargs)
        return wrapper
    return udf_docstrings

def get_registry() -> list[dict]:
    return _registry