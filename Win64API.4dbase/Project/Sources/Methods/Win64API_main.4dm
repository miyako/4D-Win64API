//%attributes = {}
  // Win64API_main
  //
  // This method will act as a unit test to the Win64API commands and a sample database to show what
  // it can do.
  //
  // ACW 10/3/19 WIN-71

C_LONGINT:C283($1;$lWinRef)

$lWinRef:=-1
If (Count parameters:C259>=1)
	$lWinRef:=$1
End if 

C_BOOLEAN:C305($bMemoryTest)

  // Turn this to true to loop over a command many times to test memory usage.
$bMemoryTest:=False:C215

  // ACW 10/16/20 WIN-71
win_71 ($bMemoryTest)

  // ACW 10/20/20 WIN-78
win_78 ($bMemoryTest)

  // ACW 10/16/20 WIN-80
win_80 ($bMemoryTest)

  // ACW 10/27/20 WIN-107
  // win_107 ($bMemoryTest)

  // ACW 10/28/20 WIN-108
win_108 ($bMemoryTest;$lWinRef)

  // ACW 1/8/21 WIN-113
win_113 ($bMemoryTest;$lWinRef)

  // ACW 1/11/21 WIN-109 This test is done on the demo dialog
  // win_109 ($bMemoryTest;$lWinRef)

  // ACW 1/12/21 WIN-111
win_111 ($bMemoryTest;$lWinRef)

  // ACW 1/14/21 WIN-112
win_112 ($bMemoryTest;$lWinRef)

  // ACW 1/14/21 WIN-114
win_114 ($bMemoryTest;$lWinRef)


  // End of demo/unit test; if we haven't hit a TRACE up until now all the commands are working as expected.
TRACE:C157
