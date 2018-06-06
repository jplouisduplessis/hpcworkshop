## Network Configuration
**Before attempting this practical ensure that your head node has internet connectivity.**

As we are in an a virtual environment, we need to add an additional network interface card. In virtual box, create an additional network interface and set it it Internal Network. This will add an additional unconfigured network adapter.

On the worker node, simply change the existing NAT inteface to Internal Network.

### Configuring internal network
The two adapters we added will be used for the private internal network of the cluster. These IP addresses will need to be assigned by hand. We will need to create/modify configuration files for these adapters on both the worker and head node. In CentOS, the configuration files are located in `/etc/syscondig/network-scipts`. Quickly check the contents of this directory.

You should have noticed that there are already a number of config files there. We need to modify the one related to our adapter. So, let us check the name(s) of our adapters.

`ip addr`

This will print a summary of all the network adapters and their IP addresses. On the head node you should see two network adpaters, one of which has your public IP address (the one that has internet access). The worker node should only have a single interface. The names should look something like *enp3s0* (or some other number). Remember these names.

**Note:** Write down the names of your adapters on your head node so that you remember which one refers to the private network, and which one is the public interface.

### Setting the static addresses
Now, on each of your nodes, modify the config file of the **private** adapter, changing the address where necessary. Your config will resemble the following:

```
    DEVICE=enp0s8
    BOOTPROTO=static
    ONBOOT=yes
    TYPE=Ethernet
    IPADDR=192.168.0.1
    #Don't need gateway on HN
    #GATEWAY=192.168.0.x
    NETMASK=255.255.255.0
    #Google public DNS
    DNS1=8.8.8.8
    IPV6INIT=no
    USERCTL=no
```

Make sure you have the correct devices names!

**Note:** This is an example of /etc/sysconfig/network-scripts/ifcfg-enp0s8. Your device names may differ, so it may be eg: /etc/sysconfig/network-scripts/ifcfg-eth1 After modifying the file(s) restart the network service:

<!-- Solution: `systemctl restart network` -->

Once the network has restarted, check your new IP address to make sure it is correct. If everything was done correctly on both machines you should be able to ping between the two nodes. So, for example, from the head node, try:

`ping 192.168.0.2`

This assumes that `192.168.0.2` is the address of you worker node.

## Configuring SSH
**SSH**, or Secure Socket Shell is the protocol we will use to log in to our worker nodes and execute programs.

`ssh username@address`

The *address* can also be a host name. See [this section](#hosts-file) for more information.

We need to disable DNS lookups on the ssh service to prevent the machine from trying to resolve IP addresses to names. To do this, we need to edit the `/etc/ssh/sshd_config` file. Find the line where you see **UseDNS** and change it to *no*. Restart the sshd service after saving.

<!-- Solution: `systemctl restart sshd` -->
We are now ready to try log in to our worker node from our head node. To login, we can run the following command:

`ssh hpc@192.168.0.2`

In this example, *hpc* is the name of our user. This user must exist on the other machine for this to work. **Note:** The first time you log in you will be prompted to accept the key from the other machine. You can enter *yes* as we trust the machine (it is our machine!).

### Checklist
Before proceeding, make sure you have checked the following:
- [x] Private internal network has been configured
- [x] You can ping between nodes
- [x] You have turned off DNS in the sshd service 
- [x] You can ssh between nodes using your user account.

## Hosts file
It can be difficult to keep track of all the IP addresses in your cluster. Also, you might need to change addresses at some point. This would mean changing all the config files too. Luckily Linux allows us to "name" our IP addresses by associating them with a name. This is done in the `/etc/hosts` file.

Add an entry in the hosts file of each node so that you can refer to the other node by name. Use the following convention:

Node | Hostname | Address
-----|----------|--------
Head | hn | 192.168.0.1
Worker | wn | 192.168.0.2

Once you have this setup, you can make use of it to ssh. For example, `ssh hpc@wn` would log into the worker node from the head node.

## Security features
Linux contains security services that are used to protect the system from attacks. However, in our workshop some of these services can interfere with our tasks, so we will turn them off. There are two things that need to be disabled. The first is **selinux**. The second is the **firewalld** service.

- **selinux** can be turned off in the `/etc/selinux/conf` folder.
- **firewalld** is a service that can be disabled.

## SSH login with keys
Many programs will make use of ssh to execute across the cluster's worker nodes. If a password is required, these jobs will fail. We can replace the password with an authorised key. An SSH key consists of a private and public key. The private key should never be shared. You can make use of the public key to login to the other nodes by adding it to the authorized_keys file on your worker node (or head node from the worker node).

To generate a key, make use of `ssh-keygen`. You can use the `ssh-copy-id` command to move the generated public key to the other node.

**Note:** In a later section we will sync the keys to all the nodes using NFS.

## Worker node internet
You may may noticed that our worker nodes don't have access to the internet. To enable access we will make use of Network Address Translation (NAT). We need to set up some rules in *IPTables* to forward packets from our internal network to the internet.

IPTables is a firewall that is widely used on GNU Linux. In recent years, RedHat and SuSE Linux moved over to FirewallD. However, a lot of GNU Linux users still prefer IPTables. The configuration of IPTables is done in the `/etc/sysconfig/iptables` file but before modifying it, we have to make sure that IPTables is installed.

```
yum -y install iptables
systemctl enable  iptables
systemctl start iptables

```
Next, we need to enable NAT-ting on the head node.

```
echo "net.ipv4.ip_forward=1" >> /etc/sysctl.conf
#Now apply the NAT configuration persistently over reboots:
sysctl -p
```

Now we can modify the `/etc/sysconfig/iptables` file.

```
*filter
:INPUT ACCEPT [0:0]
:FORWARD ACCEPT [0:0]
:OUTPUT ACCEPT [0:0]
:ET - [0:0]
:FW - [0:0]
-A INPUT -j FW
-A FORWARD -j FW
-A FW -i lo -j ACCEPT
-A FW -p icmp -m icmp --icmp-type 8 -j ACCEPT
-A FW -m state --state RELATED,ESTABLISHED -j ACCEPT
-A FW -s 192.168.0.0/24 -j ACCEPT
# Open ssh port
-A FW -p tcp -m state --state NEW -m tcp --dport 22 -j ACCEPT
# Open http port
-A FW -p tcp -m state --state NEW -m tcp --dport 80 -j ACCEPT
#The following 2 rules a required for NAT-ing
-A FW -i enp0s8 -o enp0s3 -m state --state RELATED,ESTABLISHED -j ACCEPT
-A FW -i enp0s3 -o enp0s8 -j ACCEPT
-A FW -j DROP
COMMIT
*nat
-A POSTROUTING -o enp0s3 -j MASQUERADE
COMMIT
```
**Note:** Make sure you check the names of your adapters. In this example enp0s3 is the public interface, and enp0s8 the private interface. You will need to restart iptables for the changes to take effect.

**Tip**: Whenever you are setting up a service that works through the network and it seems that it is not working, temporarily stop IPTables on both machines and try again. If it works then, make sure to add the correct entries into IPTables. Also make sure to start IPTables again afterwards. Another helpful file is:
`/etc/services`. It lists a number of standard services with the ports on which they run.

Test your internet connection on your worker nodes before proceeding.

## Network File Sharing (NFS)
NFS allows us to share files over the network. This is useful for sharing programs across all nodes, or ensuring that a user's data is distributed to all the nodes.

### Installing NFS server
This is done on the head node. First, prepare the directories that you want to share over the network. We will share the /home, a /scratch (for program data) and /var/soft (for our software).


### Installing NFS clients
This is done on the worker node.
### Making NFS persistant
Modify `/etc/fstab` file. This file stores volumes that should be mounted when the system boots up.