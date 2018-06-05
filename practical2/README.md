## Network Configuration
**Before attempting this practical ensure that your head node has internet connectivity.**

As we are in an a virtual environment, we need to add an additional network interface card. In virtual box, create an additional network interface and set it it Internal Network. This will add an additional unconfigured network adapter.

On the worker node, simply change the existing NAT inteface to Internal Network.

### Configuring internal network
The two adapters we added will be used for the private internal network of the cluster. These IP addresses will need to be assigned by hand. We will need to create/modify configuration files for these adapters on both the worker and head node. In CentOS, the configuration files are located in `/etc/syscondig/network-scipts`. Quickly check the contents of this directory.

You should have noticed that there are already a number of config files there. We need to modify the one related to our adapter. So, let us check the name(s) of our adapters.

`ip addr`

This will print a summary of all the network adapters and their IP addresses. On the head note you should see two network adpaters, one of which has your public IP address (the one that has internet access). The worker node should only have a single interface. The names should look something like *enp3s0* (or some other number). Remember these names.

***Note***
Write down the names of your adapters on your head node so that you remember which one refers to the private network, and which one is the public interface.

### Setting the static addresses
Now, on each of your nodes, modify the config file of the **private** adapter, changing the address where necessary. Your config will resemble this following:

DEVICE=enp0s8
BOOTPROTO=static
ONBOOT=yes
TYPE=Ethernet
IPADDR=192.168.0.1
#Don't need gateway on HN
#GATEWAY=192.168.xx.1
NETMASK=255.255.255.0
#Google public DNS
DNS1=8.8.8.8
IPV6INIT=no
USERCTL=no
Make sure you have the correct devices names!

**Note:** This is an example of /etc/sysconfig/network-scripts/ifcfg-enp0s8. Your device names may differ, so it may be eg: /etc/sysconfig/network-scripts/ifcfg-eth1 After modifying the file(s) restart the network service:

`systemctl restart network`

Once the network has restarted, check your new IP address to make sure it is correct. If everything was done correcntly on both machines you should be able to ping between the two nodes. So, for example, from the head node, try:

`ping 192.168.0.2`

This assumes that `192.168.0.2` is the address of you worker node.

## Configuring SSH
We need to disable DNS lookups on the ssh service to prevent the machine from trying to resolve ip addresses to names. To do this, we need to edit the `/etc/ssh/sshd_config` file. Find the line where you see **UseDNS** and change it to *no*. Restart the sshd service after saving.

We are now ready to try log in to our worker node from our head node. To login, we can run the following command:

`ssh hpc@192.168.0.2`

In this example, *hpc* is the name of our user. This user must exist on the other machine for this to work. **Note:** The first time you log in you will be prompted to accept the key from the other machine. You can enter *yes* as we trust the machine (it is our machine!).
