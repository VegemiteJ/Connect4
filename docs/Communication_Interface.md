Communication Interface
--------------------------------------
3 parts
1) JSClient - [JS]
2) NodeJS Server - [Node]
3) CPP ai Server - [CPP]

Connection setup - On page request from User browser:
=================
- Node sets up server on 21357 for JS
- Node serves board.html
- Node tests ports until it finds an availble one - $ports          //At some point will switch to cpp spawning new threads to multiplex sockets
- Node starts new CPP instance using args ['1', '$PORT']
- Node stores socket from
- CPP instance binds to $PORT and waits for connection
- JS sets up socket to Node on port 21357
- Node sets up socket to cpp on $PORT

//Node must handle the correct message forwarding
Contains Socket[NumCores].

Serves busy server page when Socket[NumCores] is full

Must store a mapping of [JSSocket, CPPSocket] so that when io.on('message') and net.on('data') it looks up the corresponding

    JSSocket or CPPSocket and correctly forwards the packet onwards

Keeps internal count of the number of active sockets - Spins up new ai whenever number of active < NumberOfCores

On disconnect, MUST teardown cpp ai process, teardown sockets and release entry in mappings of [jssocket,cppsocket]

Game In Progress
=================
JS:
- Renders board and starts a connection after at least 300ms to allow the cpp server to start correctly
- Connects to cpp server
- (a) Waits for player to trigger an event listener on a column
- Parses move
- Sends move as 1-indexed column to Node (21357)
- Sets allowedMove to false
- Wait until it receives a 1-indexed move from cpp ai via node then go back to a-
    
- When receives '-1' game is ended: Next number after 0 for loss 1 for win determines who won
        JS player or ai

Networking Codes
=================

On connection: JS sends board size Number of Rows then Number of Columns
            
    Sends (int)R then (int)C

During Game: JS sends number in range [1,NumberCols] as move
    
    CPP sends number in range [1,NumberCols] as move

On Winner: CPP sends -1, followed by 0 for AI win or 1 for JS win

