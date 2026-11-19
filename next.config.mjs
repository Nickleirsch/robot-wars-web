/** @type {import('next').NextConfig} */
const nextConfig = {
  // The wasm bundle is served straight out of public/ and loaded at runtime with
  // a bare URL import, so the bundler never touches it.
  reactStrictMode: true,
};

export default nextConfig;
