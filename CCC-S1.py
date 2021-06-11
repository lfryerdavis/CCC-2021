numPieces = int(input())

heightsStr = input()
heights = heightsStr.split(" ")

widthsStr = input()
widths = widthsStr.split(" ")

area = 0

for index in range(numPieces):
  width = int(widths[index])
  heightL = int(heights[index])
  heightR = int(heights[index+1])
  area += (heightL+heightR)*width
    
if area % 2 == 0:
  print(area // 2)
else:
  print(area/ 2.0)
