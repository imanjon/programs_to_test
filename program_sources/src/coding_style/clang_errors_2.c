void test() {
  void (*foo)(void);
  foo();	// warning: function pointer is uninitialized
}

int main(){
	test();
}
