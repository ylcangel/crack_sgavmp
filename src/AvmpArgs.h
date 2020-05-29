// 3 java.lang.Integer
// 4 java.lang.Long
// 5 java.lang.Float
// 6 java.lang.Double
// 7 java.lang.String
// 8 [B
// >8 java.lang.Boolean
struct ArgData { // 原始参数类型, 8代表内存类型, 还作为avmp模块的sign存储结构
	int type; // 对应上述值, 但是如果是字符串, 并且是执行了拷贝, 类型同样为8, 而不是7, 保存签名类型也为7
	int unused0;
	// 对于数组来说都执行复制操作, value指向新复制数据的内存地址
	// 但存在两种情况, 一种是长度和原来相同, 一种是长度比原来多4字节
	// 多4字节的情况，数组的前4字节空出来, 不作为使用
	void* data; // 原始参数对应的值, 如果是字符串类型存在两种情况, 一种是直接引用, 一种是内存拷贝指向内存地址
	// 字符串长度同原字符串长度
	// 如果保存模块签名, 是签名长度
	int dataLen; // 如果是数组, 并且是拷贝(由一个参数决定)的,它的长度是原数组长度+4, 否则为原始长度
	bool isByteArray; // 1 是, 否则是字符串
	void* unused;
}; // 最开始由Objecct[] 转换而来的

struct ModuleSig { // 对应avmp module签名
	void* signature; // 对应保存签名的vdata指针
	void* moduleVdata; // 指向新拷贝创建的XorAvmpInst->aVmpModule1的vdata
};

// +-------------------+
// |...                | // AvmpArgData
// |原参数转换后的参数 | // 个数为n
// |+------------------+ // 多出的两个参数
// | 调用avmp模块的签名| // n+1
// +-------------------+
// | 调用模块的名字    | // n+2
// +-------------------+
struct AvmpArgs { // 最终调用avmp模块的参数
	// 原参数转换为结构体AvmpArgData占24字节, 这片内存比原始多2*24字节, 假设参数个数为n,则为n+2
	struct ArgData* args; // n+1 对应avmp 模块签名, n+2对应模块名字(类型为8), 如mwua、sgcipher、sign
	int argSize; // 最后被设置为参数个数+2
	struct ModuleSig* moduleSign; // 模块签名
	int signSize; // == XorAvmpInst->signSz
};
