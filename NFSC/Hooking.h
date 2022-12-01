int HookCount = 0;
class Hooks
{
public:
	int StubAddress;
	int FunctionAddres;
	int* allocatedStub;
	void __attribute__((noinline)) Hook(int address, int Myfunction)
	{
		FunctionAddres = address;
		allocatedStub = (int*)_sys_malloc(8);
		StubAddress = 0x8DF400 + (HookCount << 5);
		allocatedStub[0] = StubAddress;
		allocatedStub[1] = TOC;
		HookFunction(FunctionAddres, StubAddress, Myfunction);
		HookCount++;
	}

	void __attribute__((noinline)) Restore()
	{
		int restorebytes[4];
		read_process(StubAddress + 0xC, restorebytes, 16);
		write_process(FunctionAddres, &restorebytes, 16);

		_sys_free(allocatedStub);
	}

	template<typename Return, typename... params>
	Return Stub(params... parameters)
	{
		Return(*callit)(params...) = (Return(*)(params...))allocatedStub;
		return callit(parameters...);
	}
};