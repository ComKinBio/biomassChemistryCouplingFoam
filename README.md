<div id="top"></div>
<!--
*** README template used
*** https://github.com/othneildrew/Best-README-Template
-->

<!-- PROJECT SHIELDS -->
<!--
*** Markdown "reference style" is used links for readability.
*** Reference links are enclosed in brackets [ ] instead of parentheses ( ).
*** See the bottom of this document for the declaration of the reference variables
*** for contributors-url, forks-url, etc.
*** https://www.markdownguide.org/basic-syntax/#reference-style-links
-->


<!-- PROJECT -->
# biomassChemistryCouplingFoam



<!-- PROJECT LOGO -->
The biomassChemistryCouplingFoam is an extended solver based on our previous developed solver "[biomassChemistryFoam](https://github.com/ComKinBio/biomassChemistryFoam)". The `biomassChemistryFoam` is renamed as `biomassChemistryIBMFoam`, IBM stands for Interface-Based Method. Compared to biomassChemistryFoam the major change is the solid volume faction is added to the governing equations. The detials are documented in the "Student tutorials" at [CFD with OpenSource Software (Course at Chalmers University of Technology)](https://www.tfd.chalmers.se/~hani/kurser/OS_CFD/) titled "Modifying coalChemistryFoam for dense gas-solid simulation". 
<br />
<br />

[![Contributors][contributors-shield]][contributors-url]
[![Forks][forks-shield]][forks-url]
[![Stargazers][stars-shield]][stars-url]
[![Issues][issues-shield]][issues-url]
[![OpenFOAM v7](https://img.shields.io/badge/OpenFOAM-v7-brightgreen.svg)](https://openfoam.org/)
[![License: GPL v3][license-shield]][license-url]

<div align="center">
  <p align="center">
    <a href="https://github.com/ComKinBio/biomassChemistryCouplingFoam/issues">Report Bug</a>
    ·
    <a href="https://github.com/ComKinBio/biomassChemistryCouplingFoam/issues">Request Feature</a>
  </p>
</div>



<!-- TABLE OF CONTENTS -->
<details>
  <summary>Table of Contents</summary>
  <ol>
    <li><a href="#about-the-project">Features</a></li>
    <li><a href="#license">License</a></li>
    <li><a href="#Contributing">Contributing</a></li>
    <li><a href="#Contact">Contact</a></li>
  </ol>
</details>



<!-- Features -->
## Features

### Coupling method

A two grid model is used here.

The drag force is calculated differently based on the equation type. Reference paper ["Discrete particle simulation of particle–fluid flow: model formulations and their applicability"](https://www.cambridge.org/core/journals/journal-of-fluid-mechanics/article/discrete-particle-simulation-of-particlefluid-flow-model-formulations-and-their-applicability/573177312329F5F2D359D18FBBD60A59).

### Solver

A single particle case is added as a test and tutorial case for this slover.

<p align="right">(<a href="#top">back to top</a>)</p>



<!-- Contributing -->

## Contributing

If you have any contribution to this repo, please fork the repo and create a pull request (to dev). You can also simply open an issue with the tag "improvement".

Besides coding, academic discussions through emails are most approciated.



<p align="right">(<a href="#top">back to top</a>)</p>



<!-- LICENSE -->
## License

Distributed under the [GPLv3 License](https://www.gnu.org/licenses/gpl-3.0.en.html). ([OpenFOAM license control](https://openfoam.org/licence/))

<p align="right">(<a href="#top">back to top</a>)</p>



<!-- CONTACT -->
## Contact

Jingyuan Zhang - jingyuan.zhang@ntnu.no 

Tian Li - tian.li@ntnu.no / tian.li@risefr.no

Henrik Ström - henrik.strom@chalmers.se


Research group: [ComKin group at NTNU](https://www.ntnu.edu/comkin/)


<p align="right">(<a href="#top">back to top</a>)</p>



<!-- MARKDOWN LINKS & IMAGES -->
<!-- https://www.markdownguide.org/basic-syntax/#reference-style-links -->
[contributors-shield]: https://img.shields.io/github/contributors/ComKinBio/biomassChemistryCouplingFoam.svg?style=flat
[contributors-url]: https://github.com/ComKinBio/biomassChemistryCouplingFoam/graphs/contributors
[forks-shield]: https://img.shields.io/github/forks/ComKinBio/biomassChemistryCouplingFoam.svg?style=flat
[forks-url]: https://github.com/ComKinBio/biomassChemistryCouplingFoam/network/members
[stars-shield]: https://img.shields.io/github/stars/ComKinBio/biomassChemistryCouplingFoam.svg?style=flat
[stars-url]: https://github.com/ComKinBio/biomassChemistryCouplingFoam/stargazers
[issues-shield]: https://img.shields.io/github/issues/ComKinBio/biomassChemistryCouplingFoam.svg?style=flat
[issues-url]: https://github.com/ComKinBio/biomassChemistryCouplingFoam/issues
[license-shield]: https://img.shields.io/badge/License-GPLv3-blue.svg
[license-url]: https://www.gnu.org/licenses/gpl-3.0

