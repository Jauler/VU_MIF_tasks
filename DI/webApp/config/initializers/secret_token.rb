# Be sure to restart your server when you modify this file.

# Your secret key is used for verifying the integrity of signed cookies.
# If you change this key, all old signed cookies will become invalid!

# Make sure the secret is at least 30 characters and all random,
# no regular words or you'll be exposed to dictionary attacks.
# You can use `rake secret` to generate a secure secret key.

# Make sure your secret_key_base is kept private
# if you're sharing your code publicly.
WebApp::Application.config.secret_key_base = '36dc75ce168fecbc4175666af99ac003f5ab760452504016fda624783183f42257f5df82b3ea57aa2c3f1db6611ac72cf5041f65ed61dadf1bb06e994c1f3ee9'
