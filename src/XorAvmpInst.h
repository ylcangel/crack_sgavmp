struct XorAvmpInst { // 它可能是个列表，一个挨着一个，代表不同的avmp实例
	void* xorAvmpinst; // avmpInst ^ time
	int timeRsr31; // 时间右移31位
	int time;
	int timersr31t; // 时间右移31位
	void* aVmpModule1; // mwua对应的vdata32
	void* aVmpModule2; // sgcipher对应的vdata32
	void* sign; // 1,1,5 生成的签名vdata
	int signSz; // 签名个数，调试时为1
	// vcode代码被异或加密
	void* vmpBuf; // bytecode字节数组
	struct XorAvmpInst* next; // 暂时未空, 多个实例的话会存在下一个
}; 