import React, { Component } from 'react';
import ReactRectangle from 'react-rectangle'
import InputMask from 'react-input-mask';

export class Sudoku extends Component {
    static displayName = Sudoku.name;

    lastCoord;

    constructor(props) {
        super(props);
        this.linear_ref_table = Array.from(Array(9), () => new Array(0))
        this.mainFrame = React.createRef();
        console.log(this.linear_ref_table)
        this.handleKeyDown = this.handleKeyDown.bind(this)
        this.renderInput = this.renderInput.bind(this)
        this.square = this.square.bind(this)
        this.nineSquares = this.nineSquares.bind(this)


        const ratio = (window.innerHeight - 150) * 100 / window.innerWidth

        this.white_style = {
            display: 'flex',
            height: '100%',
            'background-color': '#ffffff',
            'align-items': 'center',
            'justify-content': 'center',
            'transition-duration': '2s',
        }

        this.green_style = {
            display: 'flex',
            height: '100%',
            'background-color': '#99ff99',
            'align-items': 'center',
            'justify-content': 'center',
            'transition-duration': '2s',
        }

        this.red_style = {
            display: 'flex',
            height: '100%',
            'background-color': '#ff9999',
            'align-items': 'center',
            'justify-content': 'center',
            'transition-duration': '2s',
        }

        this.purple_style = {
            display: 'flex',
            height: '100%',
            'background-color': '#ff99ff',
            'align-items': 'center',
            'justify-content': 'center',
            'transition-duration': '2s',
        }

        this.style_table = Array.from(Array(9), () => new Array(9).fill(this.white_style))

        this.ref_table = Array.from(Array(9), () => new Array(9)/*.fill(React.createRef())*/)

        for (let i = 0; i < 9; i++) {
            for (let j = 0; j < 9; j++) {
                this.ref_table[i][j] = React.createRef();
            }
        }

        this.state = {
            forecasts: [], loading: true,
            fontSize: "1px",
            boardWidth: "1%"
        };
    }

    handleKeyDown(e) {
        const coord = this.findFocused()
        if (e.keyCode === 38) {
            if (coord.row > 0) {
                this.linear_ref_table[coord.col][coord.row - 1].current.getInputDOMNode().focus()
                //this.linear_ref_table[coord.col][coord.row - 1].current.getInputDOMNode().setSelectionRange(0, 0)
            }
        } else if (e.keyCode === 39) {
            if (coord.col < 8) {
                this.linear_ref_table[coord.col + 1][coord.row].current.getInputDOMNode().focus()
                //this.linear_ref_table[coord.col + 1][coord.row].current.getInputDOMNode().setSelectionRange(0, 0)
            }

        } else if (e.keyCode === 40) {
            if (coord.row < 8) {
                this.linear_ref_table[coord.col][coord.row + 1].current.getInputDOMNode().focus()
                //this.linear_ref_table[coord.col][coord.row + 1].current.getInputDOMNode().setSelectionRange(0, 0)
            }

        } else if (e.keyCode === 37) {
            if (coord.col > 0) {
                this.linear_ref_table[coord.col - 1][coord.row].current.getInputDOMNode().focus()
                //this.linear_ref_table[coord.col - 1][coord.row].current.getInputDOMNode().setSelectionRange(0, 0)
            }
        }
    }

    resizeSudoku = () => {
        const ratio = (window.innerHeight - this.mainFrame.current.offsetTop) * 100 / window.innerWidth
        const length = window.innerHeight - this.mainFrame.current.offsetTop - 65
        this.setState({
            fontSize: (ratio > 100 ? (window.innerWidth / 12) : (length / 12)) + "px",
            boardWidth: (ratio > 100 ? "100%" : (length + "px")),
        })
    }

    onScreenResize = () => this.resizeSudoku()

    componentDidMount() {
        window.addEventListener('resize', this.onScreenResize)
        this.resizeSudoku()
        console.log(this.mainFrame.current)
        //this.populateWeatherData();
    }

    componentWillUnmount() {
        window.removeEventListener('resize', this.onScreenResize)
    }

    componentDidUpdate() {
    }


    clearReferences = () => (this.linear_ref_table = Array.from(Array(9), () => new Array(0)))

    findFocused = () => {
        let smallSquare = -1
        let bigSquare = -1
        let col = -1
        let row = -1

        for (let i = 0; i < 9; i++) {
            smallSquare = this.ref_table[i].findIndex(element => element.current.isFocused() == true)
            if (~smallSquare) { // <=> if smallSquare != -1
                bigSquare = i
                break
            }
        }

        for (let i = 0; i < 9; i++) {
            row = this.linear_ref_table[i].findIndex(element => element.current.isFocused() == true)
            if (~row) { // <=> if row != -1
                col = i
                break
            }
        }
        return { bigSquare: bigSquare, smallSquare: smallSquare, col: col, row: row }
    }


    convertToLinear = (coord) => {

        //squares to linear
        coord.col = Math.floor(coord.bigSquare / 3) * 3 + Math.floor(coord.smallSquare / 3)
        coord.row = (coord.bigSquare % 3) * 3 + coord.smallSquare % 3

        return coord
    }

    convertToSquares = (coord) => {

        //linear to squares
        coord.bigSquare = Math.floor(coord.col / 3) * 3 + Math.floor(coord.row / 3)
        coord.smallSquare = (coord.col % 3) * 3 + coord.row % 3

        return coord
    }



    colorByValidity = (coord) => {

        const validity = this.squareCheckValidity(coord)

        for (let i = 0; i < 9; i++) {
            //Check if affected tiles in the 3x3 square should change their colours
            let propagatedCoord = this.convertToLinear({ bigSquare: coord.bigSquare, smallSquare: i, col: coord.col, row: coord.row })
            let propagatedValidity = this.squareCheckValidity(propagatedCoord)

            //Most of the time the square will be either valid or completed,
            //so we check these options first, and the other ones later 
            if (propagatedValidity == "valid") {
                this.style_table[propagatedCoord.bigSquare][propagatedCoord.smallSquare] = this.white_style;
            }
            else if (propagatedValidity == "completed") {
                this.style_table[propagatedCoord.bigSquare][propagatedCoord.smallSquare] = this.green_style;
            }
            else
                this.style_table[propagatedCoord.bigSquare][propagatedCoord.smallSquare] = this.red_style;

            //Check if affected tiles in the 1x9 row should change their colours
            //If tile is a part of the 3x3 square, we skip this block to not check it twice redudantly 
            if (Math.floor(i / 3) != Math.floor(coord.row / 3)) {
                propagatedCoord = this.convertToSquares({ bigSquare: coord.bigSquare, smallSquare: coord.smallSquare, col: coord.col, row: i })
                propagatedValidity = this.squareCheckValidity(propagatedCoord)
                if (propagatedValidity == "valid") {
                    this.style_table[propagatedCoord.bigSquare][propagatedCoord.smallSquare] = this.white_style;
                }
                else if (propagatedValidity == "completed") {
                    this.style_table[propagatedCoord.bigSquare][propagatedCoord.smallSquare] = this.green_style;
                }
                else
                    this.style_table[propagatedCoord.bigSquare][propagatedCoord.smallSquare] = this.red_style;
            }

            //Check if affected tiles in the 9x1 column should change their colours
            //If tile is a part of the 3x3 square, we skip this block to not check it twice redudantly 
            if (Math.floor(i / 3) != Math.floor(coord.col / 3)) {
                propagatedCoord = this.convertToSquares({ bigSquare: coord.bigSquare, smallSquare: coord.smallSquare, col: i, row: coord.row })
                propagatedValidity = this.squareCheckValidity(propagatedCoord)
                if (propagatedValidity == "valid") {
                    this.style_table[propagatedCoord.bigSquare][propagatedCoord.smallSquare] = this.white_style;
                }
                else if (propagatedValidity == "completed") {
                    this.style_table[propagatedCoord.bigSquare][propagatedCoord.smallSquare] = this.green_style;
                }
                else
                    this.style_table[propagatedCoord.bigSquare][propagatedCoord.smallSquare] = this.red_style;
            }
        }


    }

    squareCheckValidity = (coord) => {
        const val = this.ref_table[coord.bigSquare][coord.smallSquare].current.value

        if (!val)
            return "valid";

        if (this.ref_table[coord.bigSquare].filter(element => element.current.value == val).length > 1)
            return "invalid";
        else if (this.linear_ref_table[coord.col].filter(element => element.current.value == val).length > 1)
            return "invalid";
        else if (this.linear_ref_table.filter(element => element[coord.row].current.value == val).length > 1)
            return "invalid";


        else if (this.ref_table[coord.bigSquare].filter(element => !element.current.value).length == 0)
            return "completed";
        else if (this.linear_ref_table[coord.col].filter(element => !element.current.value).length == 0)
            return "completed";
        else if (this.linear_ref_table.filter(element => !element[coord.row].current.value).length == 0)
            return "completed";

        else
            return "valid";
    }

    inputValueChanged = (e) => {
        this.colorByValidity(this.lastCoord)
        if (this.style_table[this.lastCoord.bigSquare][this.lastCoord.smallSquare] == this.white_style)
            this.style_table[this.lastCoord.bigSquare][this.lastCoord.smallSquare] = this.purple_style;
        this.setState(this.state);
    }


    //Happens before "inputFocused" event
    inputLostFocus = (e) => {
        const validity = this.squareCheckValidity(this.lastCoord)
        if (validity == "valid")
            this.style_table[this.lastCoord.bigSquare][this.lastCoord.smallSquare] = this.white_style;
        else if (validity == "completed")
            this.style_table[this.lastCoord.bigSquare][this.lastCoord.smallSquare] = this.green_style;
        else
            this.style_table[this.lastCoord.bigSquare][this.lastCoord.smallSquare] = this.red_style;

        this.setState(this.state);
    }

    inputFocused = (e) => {
        this.lastCoord = this.findFocused()
        const coord = this.lastCoord

        console.log("Square: " + coord.bigSquare + " Position: " + coord.smallSquare + " Column: " + coord.col + " Row: " + coord.row)
        console.log(this.ref_table[coord.bigSquare][coord.smallSquare].current.value)
        this.style_table[coord.bigSquare][coord.smallSquare] = this.purple_style;

        this.setState(this.state);
    }

    renderInput(index) {
        //let reference = React.createRef()


        if (this.smallSquareIndex >= 9) {
            this.smallSquareIndex = 0;
            this.bigSquareIndex++;
        }


        //tylko jeden w kazdym kwadracie dostaje ref
        let reference = this.ref_table[this.bigSquareIndex][this.smallSquareIndex];

        const currentStyle = this.style_table[this.bigSquareIndex][this.smallSquareIndex];

        this.smallSquareIndex++;


        this.linear_ref_table[index].push(reference)

        return (
            <div style={currentStyle}>
                <InputMask inputmode="numeric" mask="1" onFocus={(e) => this.inputFocused(e)} onBlur={(e) => this.inputLostFocus(e)} onChange={(e) => this.inputValueChanged(e)}   ref={reference} formatChars={{ '1': '[1-9]' }} maskChar=""
                    onKeyDown={(e) => this.handleKeyDown(e)}
                    style={
                        {
                            display: 'block',
                            margin: '0 auto',
                            'background-color': 'transparent',
                            border: '0',
                            outline: '0',
                            height: '100%',
                            width: '100%',
                            'font-size': this.state.fontSize,
                            'text-align': 'center'
                        }
                    }
                />

            </div>
        )
    }

    square = (content, style, index) => {
        return (
            <ReactRectangle style={style}>
                {content(index)}
            </ReactRectangle>
        )
    }

    nineSquares = (content, outer_style, inner_style, index, step) => {
        return (

            <ReactRectangle style={outer_style}>

                <div style={{
                    display: 'flex',
                    height: '100%',
                    width: '100%'
                }}>
                    <div style={{ 'flex-grow': '1', 'flex-shrink': '1' }}>
                        {this.square(content, inner_style, index)}
                        {this.square(content, inner_style, index)}
                        {this.square(content, inner_style, index)}

                    </div>
                    <div style={{ 'flex-grow': '1', 'flex-shrink': '1' }}>
                        {this.square(content, inner_style, +step + index)}
                        {this.square(content, inner_style, +step + index)}
                        {this.square(content, inner_style, +step + index)}
                    </div>
                    <div style={{ 'flex-grow': '1', 'flex-shrink': '1' }}>
                        {this.square(content, inner_style, (2 * step) + index)}
                        {this.square(content, inner_style, (2 * step) + index)}
                        {this.square(content, inner_style, (2 * step) + index)}
                    </div>
                </div>

            </ReactRectangle>
        )
    }

    renderSudoku = () => {

        //let inside = Sudoku.square("border: '2px solid #11ffff', 'flex-grow': '1', 'flex-shrink': '1' ", "")
        const smaller_nine = (index) => (
            this.nineSquares(
                this.renderInput,
                { border: '1px solid #333333' },
                { border: '1px solid #333333', 'flex-grow': '1', 'flex-shrink': '1' }, index, 1)
        )

        return (
            <div ref={this.mainFrame} style={{
                margin: 'auto',
                width: this.state.boardWidth
            }}>
                {
                    this.nineSquares(smaller_nine, { border: '2px solid #000000' },
                        { 'flex-grow': '1', 'flex-shrink': '1' }, 0, 3)
                }
            </div>
        );
    }

    render() {
        this.clearReferences();
        this.smallSquareIndex = 0;
        this.bigSquareIndex = 0;
        let contents = this.renderSudoku(); //this.state.loading
        //? <p><em>Loading...</em></p>
        // Sudoku.renderForecastsTable(this.state.forecasts);

        return (
            <div>
                <h1 id="tabelLabel" >Sudoku</h1>
                <p>This page demonstrates a game of sudoku. Fill each field with a number between 1-9, so that each column, row, and big 3x3 square contains exactly one copy of each number.</p>
                {contents}
            </div>
        );
    }

    async populateWeatherData() {
        const response = await fetch('weatherforecast');
        const data = await response.json();
        this.setState({ forecasts: data, loading: false });
    }
}
