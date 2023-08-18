import matplotlib.pyplot as plt
import numpy as np

x = [10, 20, 30, 40, 50, 60, 70, 80, 90, 100]
y1 = [26301.29, 27092.02, 27346.78, 27642.61, 27223.14, 27180.38, 26851.50, 26901.85, 27003.93, 26077.84]

plt.plot(x, y1)
plt.title("Benchmarking(fibonacci function) with 100000 requests")
plt.xlabel("Number of concurrent requests")
plt.ylabel("Throughput(Requests/second)")
# plt.legend("Threadpool : 100")
# plt.show()

y4 = [31661.63, 32054.66, 32096.32, 32441.45, 33044.57, 32287.03, 32422.77, 32265.28, 31798.24, 32051.79]
plt.plot(x, y4)
plt.title("Benchmarking(fibonacci function) with 100000 requests")
plt.xlabel("Number of concurrent requests")
plt.ylabel("Throughput(Requests/second)")
# plt.legend("Threadpool : 150")
# plt.show()

y7 = [30633.12, 31953.28, 32196.32, 32279.04, 32850.59, 32705.73, 32070.42, 32344.51, 31819.01, 32645.03]
plt.plot(x, y7)
plt.title("Benchmarking(fibonacci function) with 100000 requests")
plt.xlabel("Number of concurrent requests")
plt.ylabel("Throughput(Requests/second)")
plt.legend(["Threadpool size : 100", "Threadpool size : 150", "Threadpool size : 200"])
plt.savefig("./plots/loadtest1.jpg")
plt.show()

y2 = [26869.08, 27794.97, 26303.57, 25961.76, 26069.26, 26562.13, 25918.39, 26649.18, 25925.35, 25483.36]
plt.plot(x, y2)
plt.title("Benchmarking(prime function) with 100000 requests")
plt.xlabel("Number of concurrent requests")
plt.ylabel("Throughput(Requests/second)")
# plt.show()

y5 = [31231.27, 32410.77, 32453.93, 32923.32, 32885.79, 32463.88, 32002.06, 32530.75, 32401.96, 33168.85]
plt.plot(x, y5)
plt.title("Benchmarking(prime function) with 100000 requests")
plt.xlabel("Number of concurrent requests")
plt.ylabel("Throughput(Requests/second)")
# plt.show()


y8 = [30945.71, 31932.16, 32957.89, 32158.50, 32487.06, 31322.86, 32662.27, 31873.51, 32511.49, 33216.64]
plt.plot(x, y8)
plt.title("Benchmarking(prime function) with 100000 requests")
plt.xlabel("Number of concurrent requests")
plt.ylabel("Throughput(Requests/second)")
plt.legend(["Threadpool size : 100", "Threadpool size : 150", "Threadpool size : 200"])
plt.savefig("./plots/loadtest2.jpg")
plt.show()

y3 = [24404.53, 24806.50, 24281.30, 25605.70, 32692.59, 33054.04, 33283.87, 32663.36, 32902.92, 32532.70]
plt.plot(x, y3)
plt.title("Benchmarking(pingpong function) with 100000 requests")
plt.xlabel("Number of concurrent requests")
plt.ylabel("Throughput(Requests/second)")
# plt.show()

y6 = [30769.52, 33271.99, 32843.46, 33052.83, 33172.88, 33223.10, 32879.40, 32801.96, 31932.44, 33190.27]
plt.plot(x, y6)
plt.title("Benchmarking(pingpong function) with 100000 requests")
plt.xlabel("Number of concurrent requests")
plt.ylabel("Throughput(Requests/second)")
# plt.show()

y9 = [31025.51, 31787.88, 32607.18, 32638.56, 32760.53, 33382.76, 32873.79, 33291.50, 32549.69, 33163.90]
plt.plot(x, y9)
plt.title("Benchmarking(pingpong function) with 100000 requests")
plt.xlabel("Number of concurrent requests")
plt.ylabel("Throughput(Requests/second)")
plt.legend(["Threadpool size : 100", "Threadpool size : 150", "Threadpool size : 200"])
plt.savefig("./plots/loadtest3.jpg")
plt.show()

