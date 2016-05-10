server_bind_addr = ("0.0.0.0", 3030)
local_bind_addr = ("127.0.0.1", 7070)

server_proxy_addr = ("107.170.71.234", server_bind_addr[1])

def encode(c):
  return chr(c^200)
