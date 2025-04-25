$(document).ready(function() {
    const clockMode = 'ticking';
    
    // Function to dynamically add clock numbers
    function addClockNumbers() {
        const clockFace = $('.clock-face');
        const radius = 140;
        const centerX = 150;
        const centerY = 150;

        for (let i = 1; i <= 12; i++) {
            const angle = (i * 30) * (Math.PI / 180);
            const x = centerX + radius * Math.sin(angle);
            const y = centerY - radius * Math.cos(angle);

            const numberDiv = $('<div>')
                .addClass('clock-number')
                .css({
                    position: 'absolute',
                    left: `${x}px`,
                    top: `${y}px`,
                    transform: `translate(-50%, -50%)`
                })
                .text(i);
                
            clockFace.append(numberDiv);
        }
    }

    addClockNumbers();

    let lastSecond = -1; // Track the last second we updated (for ticking mode)

    function updateClock() {
        const now = new Date();
        const hours = now.getHours() % 12;
        const minutes = now.getMinutes();
        const seconds = now.getSeconds();
        const milliseconds = now.getMilliseconds();
        
        // Calculate degrees for each hand
        const hourDegrees = (hours * 30) + (minutes * 0.5);
        const minuteDegrees = (minutes * 6) + (seconds * 0.1);
        
        // Determine second hand behavior based on mode
        let secondDegrees;
        let secondTransition;
        
        if (clockMode === 'ticking') {
            // Ticking mode
            if (seconds !== lastSecond) {
                lastSecond = seconds;
                secondDegrees = seconds * 6;
                secondTransition = 'transform 0.05s ease-out';
            } else {
                requestAnimationFrame(updateClock);
                return;
            }
        } else {
            // Smooth mode
            secondDegrees = (seconds * 6) + (milliseconds * 0.006);
            secondTransition = 'transform 0.05s linear';
        }
        
        // Apply rotations
        $('.hour-hand').css('transform', `rotate(${hourDegrees}deg)`);
        $('.minute-hand').css('transform', `rotate(${minuteDegrees}deg)`);
        $('.second-hand').css({
            'transform': `rotate(${secondDegrees}deg)`,
            'transition': secondTransition
        });
        
        requestAnimationFrame(updateClock);
    }
    
    // Start the clock
    updateClock();

    function addMinuteIndicators() {
        const clockFace = $('.clock-face');
        const radius = 130; // Radius of the clock
        const centerX = 150; // Center X of the clock
        const centerY = 150; // Center Y of the clock
    
        for (let i = 0; i < 60; i++) {
            const angle = i * 6; // Angle in degrees (6 degrees per minute)
            const isBold = i % 5 === 0; // Bold for multiples of 5
    
            const lineDiv = $('<div>')
                .addClass('minute-indicator')
                .css({
                    position: 'absolute',
                    width: isBold ? '2px' : '1px', // Bold lines are slightly thicker
                    height: isBold ? '15px' : '10px', // Bold lines are longer
                    backgroundColor: 'black', // Line color
                    top: `${centerY - radius}px`, // Position at the top of the clock
                    left: `${centerX}px`, // Center horizontally
                    transform: `rotate(${angle}deg) translate(-50%, 0)`, // Rotate around the center
                    transformOrigin: `50% ${radius}px`,
                });
    
            clockFace.append(lineDiv);
        }
    }
    addMinuteIndicators();
});