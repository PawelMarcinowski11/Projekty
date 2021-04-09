import React, { Component } from 'react';

export class Home extends Component {
  static displayName = Home.name;

  render () {
    return (
      <div>
        <h1>Welcome!</h1>
            <p>My name is {'Pawe\u0142'} Marcinowski and here is a little site made to showcase my projects.</p>
        <ul>
                <li><a href='/sudoku'>Sudoku</a> - fill numbers into a 9x9 board so that each unique number appears exactly once in each row, column and big 3x3 square.
                    Completing any of these will colour the tiles in green, whereas wrong moves will be highlighted in red. The board resizes itself to always fit the screen, and the font size changes accordingly.
                    If you have a keyboard with arrow keys, you can also move between adjacent tiles by pressing them.</li>
        </ul>
        <img src="https://i.kym-cdn.com/entries/icons/original/000/028/021/work.jpg" alt="It ain't much, but it's honest work" width="400" height="225" /> 
        <br/>
        <br/>
        <p>On my site I used:</p>
        <ul>
          <li><strong>refs</strong> - to access informations about multiple tiles when checking their eligibility </li>
          <li><strong>callbacks</strong> - to fire events whenever a tile gets focus, loses it, or has its value changed </li>
          <li><strong>input masks</strong> - to make sure that user can input only one character in each square, and the character has to be a number between 1 and 9 </li>
          <li><strong>events</strong> - onScreenResize to calculate board's and font size whenever window gets resized, handleKeyDown to move focus when an arrow key is pressed </li>
          <li><strong>flex box</strong> - to align squares next to eachother </li>
          <li><strong>inline styles</strong> - store styles as objects, to help change each component's appearance dynamically </li>
          <li><strong>react-rectangle</strong> - installed with npm, helps to keep each square in a fixed 1:1 ratio </li>
        </ul>
        <p>The site is based on a Visual Studio template, with React on the frontend, and ASP.NET taking care of the backend. Its elements are being gradually replaced in my free time - and, ideally, will contain more than two pages total.</p>
      </div>
    );
  }
}
