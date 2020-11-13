# sudoku solver
global Array
Array = [[0,0,0,9,0,5,3,0,0],[0,0,0,0,0,4,2,0,0],[0,9,0,0,6,0,5,0,4],[0,4,7,0,0,0,0,0,0],[0,1,0,0,3,0,0,8,0],[0,0,0,0,0,0,7,1,0],[4,0,5,0,1,0,0,3,0],[0,0,1,8,0,0,0,0,0],[0,0,6,5,0,7,0,0,0]]
#Array can be changed

def solve():
  for j in range(9):
    for i in range(9):
      if (Array[i][j] == 0):
        for k in range(1,10):
          if possible(k,i,j):
              Array[i][j] = k
              solve()
              Array[i][j] = 0
        return      
  print(Array)
  
        
  

def possible(val,y,x):
  for i in range(9):
    if Array[y][i] == val:
      return False
  for i in range(9):
    if Array[i][x] == val:
      return False
  x0 = (x//3)*3
  y0 = (y//3)*3
  for i in range(3):
    for j in range(3):
          if Array[y0+i][x0+j] == val:
            return False
  return True

def main():

  solve()
  
if __name__ == "__main__":
    main()
