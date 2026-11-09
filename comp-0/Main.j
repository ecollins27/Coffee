.class public Main
.super java/lang/Object

.method public static main([Ljava/lang/String;)V
    .limit stack 2
    .limit locals 1

    getstatic java/lang/System/out Ljava/io/PrintStream;
    iconst_3
    fconst_2
    fadd
    invokevirtual java/io/PrintStream/println(F)V

    return
.end method
