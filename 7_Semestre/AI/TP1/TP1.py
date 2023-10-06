import sys
import copy
from queue import PriorityQueue

LOG = False
logfile = "log.txt"

rows = 3
cols = 3
solution = "123456780"
MAX_ITER = 100000 # For hill climb    


def main():
    algorithm = sys.argv[1]
    board = [[0 for _ in range(cols)] for _ in range(rows)]

    for i in range(rows):
        for j in range(cols):
            arg_indx = i * rows + j + 2
            board[i][j] = sys.argv[arg_indx]
    problem = EightPuzzle()

    verboseOutput = False
    if len(sys.argv) > 11:
        if sys.argv[11] == 'PRINT': verboseOutput = True

    if algorithm == "B":
        result = bfs(EightPuzzle.getBoardCode(board), problem)
    elif algorithm == "U":
        result = uniformCostSearch(EightPuzzle.getBoardCode(board), problem)
    elif algorithm == "I":
        result = IterativeDeepeningSearch(EightPuzzle.getBoardCode(board), problem)
    elif algorithm == "A":
        result = AStar(EightPuzzle.getBoardCode(board), problem)
    elif algorithm == "G":
        result = greedyBestFirstSearch(EightPuzzle.getBoardCode(board), problem)
    elif algorithm == "H":
        result = hillClimb(EightPuzzle.getBoardCode(board), problem)
    
    
    if result:
        printSolvedPuzzle(verboseOutput, result)
    else:
        print("No solution")


class treeNode:
    # nextNode = list
    # previusNode = parent (node)
    def __init__(self, state, depth):
        self.state = state
        self.depth = depth
        self.previusNode = None
        self.nextNodes = []
    
    def setPreviusNode(self, previusNode):
        self.previusNode = previusNode

    def setNextNodes(self, nextNode):
        self.nextNodes.append(nextNode)

    def setCost(self, value):
        self.cost = value

    def __eq__(self, other):
        return self.state == other.state
    
    def __lt__(self, other):
        return self.state < self.state
    
    def __hash__(self):
        return int(self.state)
    
    def __repr__(self): 
        return "state:% s depth:% s" % (self.state, self.depth)      

class EightPuzzle:
    def __init__(self):
        self.solutionState = solution
    
    def __codeToMatrix(self, code: str):
        board = [[0 for _ in range(cols)] for _ in range(rows)]
        for i in range(rows):
            for j in range(cols):
                indx = i * rows + j
                board[i][j] = code[indx]
        return board
    
    def __whereIsTheZero(self, state:str):
        idx = state.index('0')
        return (int((idx - idx % cols)/ rows), idx % cols)
    
    def goalTest(self, state):
        return state == self.solutionState
    
    def __doMove(self, idxRows, idxCols, move, board):
        if "down" == move:
            board[idxRows][idxCols], board[idxRows+1][idxCols] = board[idxRows+1][idxCols], board[idxRows][idxCols]
        elif "up" == move:
            board[idxRows][idxCols], board[idxRows-1][idxCols] = board[idxRows-1][idxCols], board[idxRows][idxCols]
        elif "right" == move:
            board[idxRows][idxCols], board[idxRows][idxCols+1] = board[idxRows][idxCols+1], board[idxRows][idxCols]
        elif "left" == move:
            board[idxRows][idxCols], board[idxRows][idxCols-1] = board[idxRows][idxCols-1], board[idxRows][idxCols]
        
        if LOG: writeToLog(move)
        
        return board
    
    @staticmethod      
    def getBoardCode(board):
        board_code = ""
        for i in range(rows):
            for j in range(cols):
                board_code += str(board[i][j])
        return board_code
    
    def possibleMoviments(self, state):
        board = self.__codeToMatrix(state)
        idxOfZero = self.__whereIsTheZero(state)

        newState = []
        # Down
        if idxOfZero[0] + 1 < rows:
            newBoard = self.__doMove(idxOfZero[0],idxOfZero[1], "down", copy.deepcopy(board))
            newState.append(EightPuzzle.getBoardCode(newBoard))
        # Up
        if idxOfZero[0] - 1 >= 0:
            newBoard = self.__doMove(idxOfZero[0],idxOfZero[1], "up", copy.deepcopy(board))
            newState.append(self.getBoardCode(newBoard))
        # Right
        if idxOfZero[1] + 1 < cols:
            newBoard = self.__doMove(idxOfZero[0],idxOfZero[1], "right", copy.deepcopy(board))
            newState.append(self.getBoardCode(newBoard))
        # Left
        if idxOfZero[1] - 1 >= 0:
            newBoard = self.__doMove(idxOfZero[0],idxOfZero[1], "left", copy.deepcopy(board))
            newState.append(self.getBoardCode(newBoard))

        return newState

    # Count the number of pieces in the wrong place
    def degreeOfDisorder(self, state):
        value = 0
        for i in range(len(state)):
            if self.solutionState[i] != state[i]: value += 1
        return value

    def heuristicManhattanDistance(self, state):
        value = 0
        for i in range(len(state)):
            value += self.manhattanDistanceForPiece(int(i) ,int(state[i]))
        return value
   
    # Calculate the mangattan distance of a piece to its right place 
    def manhattanDistanceForPiece(self, position, piece):
        pieceNumber = int(piece)
        # Vertical Moviment
        vMov = 0
        # Horizontal Moviment
        hMov = 0
        if int(pieceNumber) == 0:
            return 0
        if piece == position:
            return 0
        
        # The first position in the board is 0
        hMov = abs(position % 3  - (piece - 1) % 3) # (piece - 1) is done so the first number in each line has mod 3 equal 0 
        newPiecePosition = (position + 1) - hMov # (position + 1) is done so the last position in each line is multiple of 3 
        vMov = (piece - newPiecePosition) // 3 if newPiecePosition > 0 else 0    

        return hMov + vMov

    @staticmethod 
    def printState(state):
        for i in range(rows):
            for j in range(cols):
                idx = i*rows+j
                if state[idx] == '0':
                    print(" ", end=" ")
                else:
                    print(state[i*rows+j], end=" ")
            print("")

class ListAndSet:
    def __init__(self, listType):
        self.listType = listType
        if listType == "priorityQueue":
            self.list = PriorityQueue()
        else:
            self.list = []
        self.set = set()

    def __addElementToList(self, elem):
        if self.listType == "priorityQueue":
            self.list.put((elem.cost, elem))
        else:
            self.list.append(elem)

    def __removeElementFromList(self, position):
        if self.listType == "priorityQueue":
            _, elem = self.list.get()
            return elem
        else:
            return self.list.pop(position)


    def addElement(self, elem):
        self.__addElementToList(elem)
        self.set.add(elem)

    def removeFirstElement(self):
        elem = self.__removeElementFromList(0)
        self.set.remove(elem)
        return elem
    
    def removeLastElement(self):
        elem = self.__removeElementFromList(-1)
        self.set.remove(elem)
        return elem  
    
    def isEmpty(self):
        return len(self.set) == 0

    def hasElement(self, elem):
        return (elem in self.set)
    
    def getElement(self, elem):
        return self.set
    
    def updateIfCostLess(self, elem: treeNode):    
     
        newSet = set([elem])
        intersection = self.set.intersection(newSet)
        oldElem = 0

        for oldElem in intersection:
            if elem == oldElem:
                break
        if len(intersection) > 0 and  elem.cost < oldElem.cost:
            self.__addElementToList(elem)
            self.set.remove(oldElem)
            self.set.add(elem)
        

        

    
def bfs(initial_state, problem: EightPuzzle):
    node = treeNode(initial_state, 0)  
    node.setCost(node.depth)

    if problem.goalTest(node.state):
        return node.state
    
    frontier = ListAndSet("list")
    frontier.addElement(node) 
    explored = set()

    while(True):
        if( frontier.isEmpty() ):
            return False
        
        node = frontier.removeFirstElement()
        explored.add(node)

        for newMove in problem.possibleMoviments(node.state):
            childNode = treeNode(newMove, node.depth+1)
            childNode.setCost(childNode.depth)
            
            node.setNextNodes(childNode)
            childNode.setPreviusNode(node)

            if (not frontier.hasElement(childNode)) and (childNode not in explored):
                # print(explored)
                if problem.goalTest(childNode.state):
                    return childNode
                frontier.addElement(childNode)
        
def uniformCostSearch(initial_state, problem: EightPuzzle):
    node = treeNode(initial_state, 0) 
    node.setCost(node.depth) 

    
    frontier = ListAndSet("priorityQueue")
    frontier.addElement(node) 
    explored = set()

    while(True):
        if( frontier.isEmpty() ):
            return False
        
        node = frontier.removeFirstElement()

        # Because the priority dont have a update method
        # So childNodes that have a lower cost than a previus state
        # In frontier, is add to the priority instead of replace old one
        # Therefore we will have a duplicated status on frontier
        # The status that have a lower will be process before
        # So when a status with higher cost is process
        # The one with the lower will be already inside the explored list
        # Therefore we can ignore the node with the highst cost
        if node in explored:
            continue

        if problem.goalTest(node.state):
            return node
        explored.add(node)

        for newMove in problem.possibleMoviments(node.state):
            #  newMove is state from node.state using a valid move
            childNode = treeNode(newMove, node.depth+1)
            childNode.setCost(childNode.depth)

            node.setNextNodes(childNode)
            childNode.setPreviusNode(node)

            if (not frontier.hasElement(childNode)) and (childNode not in explored):
                # print(explored)
                frontier.addElement(childNode)
            frontier.updateIfCostLess(childNode)


def LimitedDeepeningSearch(initial_state, problem: EightPuzzle, maxDepth):
    node = treeNode(initial_state, 0) 
    node.setCost(node.depth)

    frontier = ListAndSet('list')
    frontier.addElement(node)

    while( not frontier.isEmpty() ):
        node = frontier.removeLastElement()
        
        if problem.goalTest(node.state): return node
        if node.depth > maxDepth: continue
 
        for newMove in problem.possibleMoviments(node.state):
            childNode = treeNode(newMove, node.depth+1)
            childNode.setCost(childNode.depth)
            childNode.setPreviusNode(node)

            if (not frontier.hasElement(childNode)):
                # print(explored)
                node.setNextNodes(childNode)
                frontier.addElement(childNode)
    
    return "Empty Frontier"


def IterativeDeepeningSearch(initialState, problem):
    limit = 0
    
    while True:
        res = LimitedDeepeningSearch(initialState, problem, limit)
        limit += 1
        
        if type(res) != str: return res
        if limit > 40: break

def AStar(initialState, problem: EightPuzzle):
    node = treeNode(initialState, 0)
    node.setCost(node.depth + problem.degreeOfDisorder(node.state))
    
    frontier = ListAndSet("priorityQueue")
    frontier.addElement(node)
    
    explored = set()

    while( not frontier.isEmpty() ):
        node = frontier.removeFirstElement()
        if problem.goalTest(node.state): return node
        
        # Because the priority dont have a update method
        # So childNodes that have a lower cost than a previus state
        # In frontier, is add to the priority instead of replace old one
        # Therefore we will have a duplicated status on frontier
        # The status that have a lower will be process before
        # So when a status with higher cost is process
        # The one with the lower will be already inside the explored list
        # Therefore we can ignore the node with the highst cost
        if node in explored:
            continue

        explored.add(node)

        for newMove in problem.possibleMoviments(node.state):
            #  newMove is state from node.state using a valid move
            childNode = treeNode(newMove, node.depth+1)
            childNode.setCost(childNode.depth + problem.degreeOfDisorder(childNode.state))
            childNode.setPreviusNode(node)

            if childNode not in explored:
                if (not frontier.hasElement(childNode)):
                    node.setNextNodes(childNode)
                    frontier.addElement(childNode)
                frontier.updateIfCostLess(childNode)



def greedyBestFirstSearch(initialState, problem: EightPuzzle):
    node = treeNode(initialState, 0)
    node.setCost(problem.heuristicManhattanDistance(node.state))
    
    frontier = ListAndSet("priorityQueue")
    frontier.addElement(node)
    
    explored = set()

    while( not frontier.isEmpty() ):
        node = frontier.removeFirstElement()
        if problem.goalTest(node.state): return node
        
        # Because the priority dont have a update method
        # So childNodes that have a lower cost than a previus state
        # In frontier, is add to the priority instead of replace old one
        # Therefore we will have a duplicated status on frontier
        # The status that have a lower will be process before
        # So when a status with higher cost is process
        # The one with the lower will be already inside the explored list
        # Therefore we can ignore the node with the highst cost
        if node in explored:
            continue

        explored.add(node)

        for newMove in problem.possibleMoviments(node.state):
            #  newMove is state from node.state using a valid move
            childNode = treeNode(newMove, node.depth+1)
            childNode.setCost(problem.heuristicManhattanDistance(childNode.state))
            childNode.setPreviusNode(node)

            if childNode not in explored:
                if (not frontier.hasElement(childNode)):
                    node.setNextNodes(childNode)
                    frontier.addElement(childNode)
                frontier.updateIfCostLess(childNode)

def hillClimb(initialState, problem: EightPuzzle):
    node = treeNode(initialState, 0)
    node.setCost(problem.heuristicManhattanDistance(node.state))
    
    explored = set()

    for _ in range(MAX_ITER):
        bestCostChildNode = treeNode('', 0)
        bestCostChildNode.setCost(100000)

        for newMove in problem.possibleMoviments(node.state):
            #  newMove is state from node.state using a valid move
            childNode = treeNode(newMove, node.depth+1)
            childNode.setCost(problem.heuristicManhattanDistance(childNode.state))
            childNode.setPreviusNode(node)

            if childNode not in explored:
                node.setNextNodes(childNode)

                if childNode.cost <= bestCostChildNode.cost:
                    bestCostChildNode = childNode
            
        if bestCostChildNode.cost <= node.cost:
            node = bestCostChildNode
        else: break
    
    return node


def printSolvedPuzzle(verbose: bool, node: treeNode):
    print(node.depth)
    # Print the intermediate steps
    if verbose:
        recursiveintermediateSteps(node)

    
def recursiveintermediateSteps(node: treeNode):
    # if node has something
    if node:
        recursiveintermediateSteps(node.previusNode)
        print("")
        EightPuzzle.printState(node.state)

def writeToLog(string: str):
    with open(logfile, 'a') as file:
        file.write(string + '\n')
        file.close() 

if __name__ == "__main__":
    main()