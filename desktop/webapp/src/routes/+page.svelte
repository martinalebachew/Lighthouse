<script lang="ts">
</script>

<svelte:head>
    <title>Lighthouse</title>
</svelte:head>

<main>
    <h1 class="title">Lighthouse</h1>
    <section class="status--container">
        <div class="status">
            <div class="status__indicator"></div>
            <p class="status__name">Systems</p>
        </div>
        <div class="status">
            <div class="status__indicator"></div>
            <p class="status__name">Virtual Lan</p>
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
                <li>Lorem, ipsum.</li>
                <li>At, consequuntur?</li>
                <li>Veritatis, hic?</li>
                <li>Autem, explicabo.</li>
                <li>Quidem, quibusdam.</li>
                <li>Reiciendis, reprehenderit.</li>
                <li>Illum, autem!</li>
            </ul>
            <ul class="information__list">
                <li>Lorem, ipsum.</li>
                <li>Rem, nam.</li>
                <li>Ad, dolorem.</li>
                <li>Delectus, earum.</li>
                <li>Optio, ipsa?</li>
                <li>Rem, omnis?</li>
                <li>Eum, natus.</li>
            </ul>
        </div>
        <article class="information--column">
            <h2 class="information__title">Server Information</h2>
            <ul class="information__list">
                <li>Lorem, ipsum.</li>
                <li>Dignissimos, at.</li>
                <li>Pariatur, saepe.</li>
                <li>Hic, sapiente?</li>
                <li>Exercitationem, ea?</li>
                <li>Repudiandae, qui.</li>
                <li>Earum, laboriosam.</li>
            </ul>
            <ul class="information__list">
                <li>Lorem, ipsum.</li>
                <li>Odio, similique!</li>
                <li>Quaerat, omnis.</li>
                <li>Possimus, eveniet.</li>
                <li>Vel, aliquam.</li>
                <li>Nobis, deserunt?</li>
                <li>Omnis, cupiditate?</li>
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

        --fs-small: 1.25rem;
        --fs-medium: calc(var(--fs-small) * 1.618);
        --fs-big: calc(var(--fs-medium) * 1.618);

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
    }

    main {
        padding: 2rem;
        padding-bottom: 0;
    }

    main > * {
        margin-bottom: 3rem;
    }

    /* title */
    .title {
        font-family: var(--font-family);
        font-size: var(--fs-big);
        color: var(--secondary-clr);
    }

    /* status */
    .status--container {
        display: grid;
        grid-template-columns: repeat(2, 1fr);
        column-gap: 4rem;
        width: fit-content;
    }

    .status {
        display: flex;
        align-items: center;
        font-family: var(--font-family);
        font-size: var(--fs-small);
        color: var(--secondary-clr);
        white-space: nowrap;
    }

    .status__indicator {
        border-radius: 50%;
        height: 1ch;
        width: 1ch;
        margin-right: 1ch;
        background-color: var(--status-green);
        box-shadow: 0 0 .25rem var(--status-green);
    }

    /* information */
    .information {
        display: flex;
        font-family: var(--font-family);
        color: var(--secondary-clr);
    }

    .information--column {
        display: grid;
        grid-template-columns: repeat(2, 50%);
        justify-items: baseline;
        column-gap: 4rem;
    }

    .information--column:first-child {
        margin-right: 6rem;
    }

    .information__title {
        width: 100%;
        grid-column: span 2;
    }

    .information__list {
        list-style: none;
        white-space: nowrap;
    }

    /* buttons */
    .buttons {
        display: flex;
        gap: 1rem;
        width: 40%;
    }

    .button {
        padding: .5rem 1rem;
        background-color: var(--accent-clr);
        border: none;
        font-family: var(--font-family);
        color: var(--secondary-clr);
        border-radius: .75rem;
        white-space: nowrap;
        cursor: pointer;
    }

    .button:not(:last-child) {
        margin-right: 1rem;
    }
    
    .button:nth-child(3) {
        margin-left: 4rem;
    }
</style>
