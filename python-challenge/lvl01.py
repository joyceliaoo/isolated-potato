alph = "abcdefghijklmnopqrstuvwxyz"
trans_alph = "cdefghijklmnopqrstuvwxyzab"


def transform(s):
    t = s.maketrans(alph, trans_alph)
    return s.translate(t)
    

print(transform('''g fmnc wms bgblr rpylqjyrc gr zw fylb. rfyrq ufyr
    amknsrcpq ypc dmp. bmgle gr gl zw fylb gq glcddgagclr ylb rfyr'q ufw 
    rfgq rcvr gq qm jmle. sqgle qrpgle.kyicrpylq() gq pcamkkclbcb.
    lmu ynnjw ml rfc spj.'''))
print(transform("map"))
