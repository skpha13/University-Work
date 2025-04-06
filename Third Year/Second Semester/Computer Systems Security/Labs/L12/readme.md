# Lab 12

## 1

![Digital Certificate](./imgs/certificate_01.png)
![Digital Certificate](./imgs/certificate_02.png)
![Digital Certificate](./imgs/certificate_03.png)

### a

Let's Encrypt

### b

Not Before: Sun, 23 Feb 2025 21:38:26 GMT
Not After:  Sat, 24 May 2025 21:38:25 GMT

### c

2048

### d

`65537`

The exponent `65537` is chosen because it has only 2 bits set to 1, making exponentiation faster. It is also standardized and widely used by cryptographic libraries.

All other certificates in the chain will also typically use `65537`, which is secure and does not pose a problem since the exponent is not secret. The security of RSA encryption relies on the modulus `n` (the product of two large primes), not the exponent.

## 2

### c

Passphrase = "parola123"

It adds a new layer of security. Even if the attacker gets a hold of the private key, he still needs to know the passphrase to use it.

### f

Public Key:

```
---- BEGIN SSH2 PUBLIC KEY ----
Comment: "rsa-key-20250331"
AAAAB3NzaC1yc2EAAAADAQABAAABAQCM+kV/+1o/+f4cpUCYeit1r6vSEtxY4Cfm
L6QwF50I5ebyFVOd8mH/ADjOcLly9e/CSZjQUYcRZ0tSFFYqWynMRU0mj3mD9G6V
aPnKF62NRJ9feHKOhngCkGWUn+1DHNFbaPuXi3C97kk/rCn5QBEjojMYc+WL6Uhb
4DnEMs8idIJFaZRyBaaAxa1IFfHLqhV44i1kgeyEyKoA1dRQoEJOagUGtgqnfLYe
oaPf/2WbeA/4uzn0sxGLgXaABnyFUBc4KXQ685Dp2eYvmr9XP9axVHwHBSGnvZuE
lEM3rLuTfj0PmXHeljsKLNzf+fesw63rJeFGEkfTqr3Pbp/E0XGF
---- END SSH2 PUBLIC KEY ----
```

---

Private Key:

```
PuTTY-User-Key-File-3: ssh-rsa
Encryption: aes256-cbc
Comment: rsa-key-20250331
Public-Lines: 6
AAAAB3NzaC1yc2EAAAADAQABAAABAQCM+kV/+1o/+f4cpUCYeit1r6vSEtxY4Cfm
L6QwF50I5ebyFVOd8mH/ADjOcLly9e/CSZjQUYcRZ0tSFFYqWynMRU0mj3mD9G6V
aPnKF62NRJ9feHKOhngCkGWUn+1DHNFbaPuXi3C97kk/rCn5QBEjojMYc+WL6Uhb
4DnEMs8idIJFaZRyBaaAxa1IFfHLqhV44i1kgeyEyKoA1dRQoEJOagUGtgqnfLYe
oaPf/2WbeA/4uzn0sxGLgXaABnyFUBc4KXQ685Dp2eYvmr9XP9axVHwHBSGnvZuE
lEM3rLuTfj0PmXHeljsKLNzf+fesw63rJeFGEkfTqr3Pbp/E0XGF
Key-Derivation: Argon2id
Argon2-Memory: 8192
Argon2-Passes: 34
Argon2-Parallelism: 1
Argon2-Salt: 8157d7b280db5fcfeaa8af19fe6d61f9
Private-Lines: 14
QI4D5ecX9OeVuK3YRCxJeQY/b/3JBvs17ilgJbXsGpO3DySMm7BxMTWW0aUYXZFJ
adm7NLbtDUKJbsNiJ7FbxjE0wY5QovCj9CDKEafFvt0Cs6gDJP4XtwUOV6Qdg/v1
HeyGLBGd5vXuwCANZEEs9AwHMjHCbinRXclXjFJV3IKdHK0yhPvLatWTlAvuik8W
oE2JzMojAoHe8SNpe0Y+9JOk4iRx6KghXZTV21TxB80Bk70XY07TFrZveZKzKiIT
sqF3wK+U9eszOT/KCxrqOOGLqbAVGe0Cd+CDOYS62oEZIto+EQjOw1qxOwq23i52
o6RHJ6O4Okgl60EN0pXGAbrFJfXA5B3723iBZsTKprLheLyQRSFcIfigCh6khOQV
nEVHfoIrgzUDmmJEmOLyZr5O/hN0oOXcVaryIZo6DWQsbWghlF0D+8LB+bgSMaNw
7vBK2LGmfZgHwqb61cQmNQc7yfly03/nEOteSR4TOU5sd9EHh/NRmsy+sz7SGFVI
/VlWoKCDEBDmhWRZ22wKV5NgxZ12mbQMBZhtYL7XGVEFGgnf4vetWroYepBMCPeA
ukHxnZxvs2e9OuVaTUcuCGw/HI9ayOXsUpj3CeS90flJbvhrwGUjSwxUc69vgwd0
MmCRGOczah/81MuybgG6IHEQzvdNRjQvYb717ZkEmkTFwc+qbLzZwFEmNhBEiKU7
VDw/K5ifFiZT9s+TBJcZQMJz1EiwVdQF4xMp0jiI/BeHf+fAllTB4BB2DMUZ2lno
vu7fcdY6RCf7srmN46j0dkxSLiQneog5EHoAUWo1PVHHKLwGwksCrbUar8bIfO3n
HZ+7te+UZr6lfdJu5tMP2Q65dx5r2JnO++Ib9//2ih+KzWgvnUd8adw8UF80yY69
Private-MAC: f2cb45d2d1b5332df95a7c4d9150afdc717c75d6e73d7f86980c5b693da6289f

```

---

OpenSSH Key:

```
-----BEGIN RSA PRIVATE KEY-----
Proc-Type: 4,ENCRYPTED
DEK-Info: DES-EDE3-CBC,B66FAC939679AE14

e6aBnxnzRHCEENw4ttqGKXuVsbTw6NNOhsmVmLuCWysNInMKeb9hC4+Jk1MA0IDa
qL40rLX0Bc75hmqQrbT0ZImL2g8o1dCO33XWKtCaC4/0n4JPDTTxXSpnaqMMDT//
pZBBW1mv/Z090VOIYYYuteLFR83XnqHRBtdzXWuj+Ii2ikRTmJGdTAzFvKJELdow
4Ql192gOgNgaKPoRwivB0bTygfgOnV/5lhthqRWnClQ5XDVO30hjaKQzl4qH81Cu
ZzLKRZbPdf+a2QSGO0PRV5fgr8+X1q4o977jxs3hVkmT5MykSqz1kLoDVXGVsL/Y
d62S+TQYbGEUrrflp5R+mClUBzwRkCBsTWgJ6QOo+pvWrtoQ4SiE1gEr/zzDmRbG
wa9tiaHUKk30Y5TLHQmdZydKRzO36nUgBY+QNeDSvltSE5wSz0jyH2nTNH3MB5Ts
g7Bo/yqtrpk+yif8W/9jcPn2u9fERR0bjUAKoCd5jKA4LOfbWjdW9zL4OWg7m6vQ
EMcAMRH7rbS2YIOwLdWDa0MipjevT7y072DL96ANslvFC7wAvzkDXnJnFmgydVUY
01WvJAUAayIS56xtp8b2SqIESlMcbGJL7lO2megh305/cH/2wz6+eAWZ8MBtvU2z
mSBNk7OGk76PzCDQaDDTmCdYq4AHLQn4I6bfofaF2fBcsfmi2Jz5ozDwkDypxjbd
Cw6OR49SvRNVp/IARJwVmhMVYJvfSLe1dZ6TSqbMq1U4KzIVBns8MUjVjh9kgc5E
7FWtHd3iTAaOKsL0YEliSG8r/JGJnRVsgMloAjhsuDSnTanY1dSNiJTzYHWdK9Wk
2LrdwgUbcepUmmxQfmVo63eqd4EZBZsxUCr7gOYWw6Tzjb9KQCHkzrTzU/BpnAMk
Q4INtAbg+KcpdwJ2eVySePOee/FfaeECmjnKAw+KT/Nqlp6q1rzAX5MQ5rcyGdIm
ExiahtfH+df8mGqNcvq2IilYVfroiYJftM4DvfCB++vInEWPkTUNfT5fFRXEttCo
TgoC2Sm+wYeQOLHNMecAVqJSjbHbMq/bZmjpxfVYL4+bjgZZAhN4GUFbjLFGM+u4
Gq1QOYv5CxRGkj+dT3zh6lgyhrj7a/uNvXqr1r+jpKZIjGuDd3I/nJwdCXbb6Rty
ETXJD1CrrJsOE6V92XYjfZjlb55BhLw23UT+aCBOYnYG+2CxRqCuWnUsAe7hHAX7
wVCcEJNERyBSbDUxE4VYmY7xUB8f0KiKXFu3dgn/kCLpMqGm4666Z5+6k0JZXG95
LFkLLpcCwozhfOzMDSIrNwe0naFnPngpRpO1FgfBDm9K5g9Ooz/T15bG8UikomNf
/r0pryHtSG2stxL5aYvmfA+iTIBnxeN0WeOD5qzPC5hSaPeN8bCZxUZQS+jkd4ch
2sWf9jXFjl7n+Xfth0hXXu2/uYcVGpu3MnFGAZeKPt/WSCU6aPVyvhWe5anZTWZc
o6wwNwrkeu4YsrIF0HAy25nk22SdOTnZyUI46zO0DznZhzBvP7xmVzqaXfl9r7n7
pikLH8ZXE3is8PQm/DsmJaPMBlm2Hsx9MQ+WnoGw30WGWr4PXpMcQw==
-----END RSA PRIVATE KEY-----
```