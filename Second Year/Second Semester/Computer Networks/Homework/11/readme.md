### 11.2

| Device       | Default Gateway |
|--------------|-----------------|
| Room-145     | 172.14.5.1      |
| Room-146     | 172.14.10.1     |
| Manager-A    | 172.14.5.1      |
| Reception-A  | 172.14.5.1      |
| Manager-B    | 172.14.10.1     |
| Reception-B  | 172.14.10.1     |

### 11.3

**ManagerA:**
   - 172.16.10.1
   - fe80::1

**Accounting.pka:**
   - 172.16.10.1
   - fe80::1

**ManagerB:**
   - 172.16.10.65
   - fe80::1
	
**Website.pka**
   - 172.16.10.65
   - fe80::1

### 11.4

**Branch-A**
- **G0/0:** 172.20.16.0/23
- **G0/1:** 172.20.18.0/24

**Branch-B**
- **G0/0:** 2001:DB8:FADE:00FF::1/64
- **G0/1:** 2001:DB8:FADE:0100::1/64


| Device | Interface | IP Address/Prefix           | Default Gateway |
|--------|-----------|-----------------------------|-----------------|
| PC-A1  | NIC       | 172.20.16.254 255.255.255.252 | 172.20.16.1     |
| PC-A2  | NIC       | 172.20.18.254 255.255.255.0   | 172.20.18.1     |
| PC-B1  | NIC       | 2001:DB8:FADE:00FF::0010/64   | fe80::B         |
| PC-B1  | NIC       | 2001:DB8:FADE:0100::0010/64   | fe80::B         |

### 11.5

| Network | Subnet Address       |
|---------|----------------------|
| Staff   | 192.168.0.0/25       |
| Sales   | 192.168.0.128/26     |
| IT      | 192.168.0.192/27     |
| Guest   | 192.168.0.224/27     |

### 11.6

**Retea:** 192.168.0.0

**1**
   - 20 host uri
   - 192.168.0.2 - S1
   - 192.168.0.1 df gateway
   - 192.168.0.3 255.255.255.224

**2**
   - 10 host uri
   - 192.168.0.34 S2
   - 192.168.0.33 df gateway
   - 192.168.0.35 255.255.255.240

**Parole:**
   - **enable:** Ciscoenpa55
   - **console:** Ciscoconpa55
   - **vty:** Ciscovtypa55
        - **SSH:**
            - user: Admin01
            - password: Admin01pa55