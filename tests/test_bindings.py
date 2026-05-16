import os
import sys
import unittest

# Ensure the build output directory is on PYTHONPATH when running from the repo root.
BUILD_DIR = os.path.abspath(os.path.join(os.path.dirname(__file__), '..', 'build'))
if BUILD_DIR not in sys.path:
    sys.path.insert(0, BUILD_DIR)

class TestBindings(unittest.TestCase):
    def test_auth_manager_binding(self):
        import auth_module

        auth = auth_module.AuthManager()
        record = auth.register_user("test_user", "secure_password")

        self.assertEqual(record.login, "test_user")
        self.assertTrue(record.hash)
        self.assertTrue(record.salt)
        self.assertTrue(auth.verify_user("test_user", "secure_password", record.hash, record.salt))
        self.assertFalse(auth.verify_user("test_user", "wrong_password", record.hash, record.salt))

    def test_crypto_engine_binding(self):
        import crypto_module

        engine = crypto_module.CryptoEngine()
        salt = engine.generate_salt()
        self.assertTrue(len(salt) > 0)

        hashed = engine.hash_password("secure_password", salt)
        self.assertTrue(len(hashed) > 0)
        self.assertTrue(engine.secure_compare(hashed, hashed))
        self.assertFalse(engine.secure_compare(hashed, "different"))

if __name__ == "__main__":
    unittest.main()
