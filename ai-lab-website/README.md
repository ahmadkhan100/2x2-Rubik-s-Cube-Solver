# AI Lab Website

A modern, responsive landing page showcasing AI Lab's suite of next-generation AI coding agents.

## Features

- Eye-catching hero section with animated background
- Product showcase highlighting the AI lab's capabilities
- Technology overview and differentiators
- About section with mission statement and animated stats
- Contact/CTA section with interactive email capture
- Dark mode toggle with persisted preference
- Smooth scrolling, intersection-based animations, and responsive layout
- Accessible, SEO-friendly structure

## Getting Started

This is a static frontend site. You can preview it locally in a few different ways:

### Option 1: Open directly in your browser
1. Locate the `index.html` file in the `ai-lab-website` directory
2. Double-click `index.html` to open it in your preferred browser

### Option 2: Serve with a simple HTTP server
If you prefer to view the site via `http://localhost`, you can use Python's built-in web server:

```bash
cd ai-lab-website
python3 -m http.server 8080
```

Then visit [http://localhost:8080](http://localhost:8080) in your browser.

> **Note:** Any static file server (Node, Ruby, etc.) will work if you prefer another tool.

## Deployment

Because this is a static site, deployment is straightforward. You can host it on any static hosting provider such as GitHub Pages, Netlify, or Vercel:

1. Upload the contents of `ai-lab-website` to your hosting provider.
2. Ensure `index.html` is set as the entry point.
3. (Optional) Configure caching and compression settings for optimal performance.

## Project Structure

```
ai-lab-website/
├── index.html   # Main landing page with inline CSS & JS for easy deployment
└── README.md    # Setup and deployment instructions
```

## Customization

- To update colors or typography, adjust the CSS variables at the top of `index.html`.
- Modify hero/product/about/contact content directly within the HTML sections.
- Extend animations or behaviors by editing the JavaScript near the bottom of the file.

## Accessibility & Performance

- Uses semantic HTML5 elements for improved accessibility and SEO.
- Includes `prefers-reduced-motion`-friendly animations (no excessive motion loops).
- Responsive layouts scale gracefully across mobile, tablet, and desktop devices.

## License

This project inherits the license of the parent repository.
