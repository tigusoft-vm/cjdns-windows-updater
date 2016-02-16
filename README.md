Tiguupdater
===========

The Tigu Updater is a small program that downloads updates to other applications in cryptographically secure way.

Goals:
======
- currently this is developed to be the updater for the cjdns (cjdns-ext) program, but could handle other ones as well
- download update using one some available Download-Method (see below)
- check the update file integrity / authenticity, by some available Signature-Method
- download, unpack the file (be totally resistant to any malicious data, until confirmed that it's authenticated)
- stop old program, replace the program files, run the new version

Download-Method
===============

Can be either:

- http download
- (https is not needed that much, and not supported at the moment)
- (file "download" will be supported in future - look for the update in given directory and the usual Downloads directory)

Signature-Method
================

We recommend to use Geport (SHA512) plus GPG (RSA 4K) as the signatures, the GPG part is well-known, and the Geport part is very QC resistant.

In future we will recommend:
- for typical software: GPG (RSA 4K) + NTru + SIDH on each update, and Geport to change the keys when compromised (and each year)
- for critically important software: GPG (RSA 8K or more) + NTru + SIDH + Geport on each update
- for embbed/super light software: NTru + SIDH. Optionally Geport to rotate keys.

- PGP signature (checked with GPG).
.. - very well-known algorithm and implementation 
.. - NOT quantum-computers safe, based on RSA (or ECDSA) plus hash [unless there will be GPG version that moves to other pubkey algorithm)
.. - Using GPGME library, along with gnupg installation in system/user
.. - On Linux: this is tested and used
.. - On Windows: there is currently a bug resulting in this option not working
.. - On Mac: this is not yet supported
.. - On ANY system how ever: the user can manually use the created .sig file himself too (e.g. to later use manual file installation)

- Own RSA implementation was considered:
.. - options were: boost big int (wrapping GMP) - but timing attacks(?)
.. - cryptopp's integer - but timing attacks(?)
.. - cryptopp RSA
.. - wolfssl RSA
.. - openssl RSA


- Geport signature (modification of Lamport signature) see project https://github.com/tigusoft/evercrypto
.. - very easy to understand and obviously safe mathematic principle of the algorithm (though the implementation is experimental as of 2016-02)
.. - QC resistant ! (as much as underlying hash function)
.. - we recommend SHA512 variant (or stronger)
.. - used in the form of block-tree (building a tree of signatures, because we replace the signing key after each one use of it)

- NTru is considered as light QC-resistant sign (pending implementation).

- SIDH is considered in future as additional light QC-resistant sign.


