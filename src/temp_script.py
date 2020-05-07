for i in range(0, 256):
    print "set_idt_entry ({0}, isr{0}, 0X08, 0X8E)".format(i)
