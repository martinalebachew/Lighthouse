<script lang="ts">
</script>

<svelte:head>
    <title>Lighthouse</title>
</svelte:head>

<div class="bar"></div>
<main>
    <h1 class="title">Lighthouse</h1>
    <section class="status--container">
        <div class="status">
            <div class="status__indicator"></div>
            <p class="status__name">All Systems Functional</p>
        </div>
        <div class="status">
            <div class="status__indicator"></div>
            <p class="status__name">Virtual LAN</p>
        </div>
        <div class="status">
            <div class="status__indicator"></div>
            <p class="status__name">Core Container</p>
        </div>
        <div class="status">
            <div class="status__indicator"></div>
            <p class="status__name">GUI Data Bridge</p>
        </div>
    </section>
    <section class="information">
        <div class="information--column">
            <h2 class="information__title">Client Information</h2>
            <ul class="information__list">
                <li>Machine Name</li>
                <li>Activation Status</li>
                <li>Edition</li>
                <li>Method</li>
                <li>Last Renewal</li>
                <li>Next Renewal</li>
                <li>Interval</li>
            </ul>
            <ul class="information__list">
                <li>DESKTOP-M127APQ</li>
                <li>Licensed</li>
                <li>Windows 10 Education</li>
                <li>Lighthouse KMS</li>
                <li>12 October 2022</li>
                <li>2 February 2023</li>
                <li>Approx. 4 Months</li>
            </ul>
        </div>
        <article class="information--column">
            <h2 class="information__title">Server Information</h2>
            <ul class="information__list">
                <li>Version</li>
                <li>KMS</li>
                <li>Virtual IP</li>
                <li>Core Container</li>
                <li>Database</li>
                <li>Updates</li>
                <li>Logs</li>
            </ul>
            <ul class="information__list">
                <li>Lighthouse 1.0</li>
                <li>6.0</li>
                <li>192.168.1.27</li>
                <li>Online</li>
                <li>KMSData 1.0</li>
                <li>Latest Version</li>
                <li>Click to view</li>
            </ul>
        </article>
    </section>
    <section class="buttons">
        <button class="button">Change Edition</button>
        <button class="button">Rearm Machine</button>
        <button class="button">Activate Now</button>
        <button class="button">Quit</button>
    </section>
</main>

<style>
    @font-face {
        font-family: "Inter";
        font-weight: normal;
        src: url("/fonts/Inter-Regular.ttf") format(TrueType);
    }

    @font-face {
        font-family: "Inter";
        font-weight: bold;
        src: url("/fonts/Inter-Medium.ttf") format(TrueType);
    }

    :global(:root) {
        --primary-clr: #202528;
        --secondary-clr: #fefefe;
        --accent-clr: #3b3f45;

        --fs-buttons: 17.72px;
        --fs-small: 17.727px;
        --fs-medium: 18.68px;
        --fs-big: 43.275px;

        --status-green: #21be72;
        --status-yellow: #eec83f;
        --status-red: #f43434;

        --font-family: 'Inter';
    }

    :global(*) {
        margin: 0;
        padding: 0;
        box-sizing: border-box;
    }

    :global(body) {
        background-color: var(--primary-clr);
        user-select: none;
        cursor: default;
    }

    .bar {
        position: absolute;
        inset: 0;
        height: 100vh;
        width: 26px;
        background-color: var(--accent-clr);
    }

    main {
        position: relative;
        padding: 46px 60px 46px 72px;
        font-family: var(--font-family);
        font-size: var(--fs-small);
    }

    /* title */
    .title {
        font-size: var(--fs-big);
        font-weight: bold;
        color: var(--secondary-clr);
        margin-bottom: 30px;
    }

    /* status */
    .status--container {
        display: grid;
        grid-template-columns: repeat(2, 1fr);
        column-gap: 62px;
        width: fit-content;
        margin-bottom: 34px;
    }

    .status {
        display: flex;
        margin-bottom: 5px;
        font-size: var(--fs-small);
        color: var(--secondary-clr);
        white-space: nowrap;
        letter-spacing: -.18px;
    }

    .status__indicator {
        border-radius: 50%;
        height: 13px;
        width: 13px;
        margin-right: 10px;
        margin-top: 2px;
        background-color: var(--status-green);
        box-shadow: 0 0 .25rem var(--status-green);
    }

    /* information */
    .information {
        display: flex;
        color: var(--secondary-clr);
        margin-bottom: 50px;
    }

    .information--column {
        display: grid;
        grid-template-columns: repeat(2, 50%);
        justify-items: baseline;
        column-gap: 32px;
    }

    .information--column:first-child {
        margin-right: 122px;
    }

    .information--column:nth-child(2) {
        column-gap: 60px;
    }

    .information__title {
        width: 100%;
        grid-column: span 2;
        font-size: var(--fs-medium);
        letter-spacing: -.1px;
    }

    .information__list {
        list-style: none;
        white-space: nowrap;
        line-height: 26px;
        letter-spacing: -.275px;
        margin-top: 3px;
    }

    /* buttons */
    .buttons {
        display: flex;
        gap: 1rem;
        width: 40%;
    }

    .button {
        cursor: pointer;
        padding: .5rem 14.48375px;
        background-color: var(--accent-clr);
        border: none;
        font-size: var(--fs-buttons);
        color: var(--secondary-clr);
        border-radius: .75rem;
        white-space: nowrap;
        cursor: pointer;
        transition: background-color 125ms ease-in-out;
        letter-spacing: .3px;
    }

    .button:hover {
        background-color: var(--status-green);
    }

    .button:last-child:hover {
        background-color: var(--status-red);
    }

    .button:not(:last-child) {
        margin-right: 19.27px;
    }
    
    .button:nth-child(3) {
        margin-left: 267.76px;
    }
</style>
